#include "GraphProblemHandler.hpp"

#define UNKOWN_ALG throw std::runtime_error("Got unkown algoritem")
#define INT_ROW_WITH_TWO_VALUES throw std::runtime_error("One of the rows with two values doesn't contain int")
#define ROW_WITH_TWO_VALUES_MISSING throw std::runtime_error("One of the rows with two values is missing")
#define VALUE_ERROR throw std::runtime_error("Invalid matrix's value")
#define NUM_VALUES_ERROR throw std::runtime_error("Num of values in matrix's row not equals to matrix width")
#define VALUE_IS_NOT_POSITIVE throw std::runtime_error("Value in the matrix must be positive")
#define MISSING_ROW_ERROR throw std::runtime_error("Missing row in the problem data")

using namespace server_side;

std::unique_ptr<solver::solution::MatrixGraphSolution> GraphProblemHandler::getSolution(
        SocketOStream* out, std::string alg) const{

        if(alg.compare(DEFAULT_ALG) == 0) {//gets the default alg if needed.
                alg = GRAPH_DEFAULT_ALG;
        }

        std::unique_ptr<solver::solution::MatrixGraphSolution> graphSolution;
        
        //geting the alg according to its name.
        if(alg.compare("DFS") == 0) {
                graphSolution = std::make_unique<solver::solution::graph_solution::DFS>();

        } else if(alg.compare("BFS") == 0) {
                graphSolution = std::make_unique<solver::solution::graph_solution::BFS>();

        } else if(alg.compare("BestFS") == 0) {
                graphSolution = std::make_unique<solver::solution::graph_solution::BestFS>();
                        
        }else if(alg.compare("A*") == 0) {
                graphSolution = std::make_unique<solver::solution::graph_solution::AStar>();
                        
        } else {
                out->writeOneMassege(SocketOStream::NO_RESPONSE, SocketOStream::NOT_SUPPORTED_ALG);
                UNKOWN_ALG;
        }

        return graphSolution;
}

void GraphProblemHandler::getMatixRaw(std::string row, SocketOStream* out,
         matrix::MatrixClass* matrix, std::uint32_t rowIndex) const {

        // we want that before every "," would be value
        // and that after the last "," would be char.
        // for easy parsing. 
        row = row + ",";

        //parsing the row & put it in the matrix
        std::uint32_t valLoc = 0;
        std::size_t found = row.find_first_of(",");
        while(found != std::string::npos) {
                //gets the value string.
                double val = 0;
                std::string valStr = row.substr(0, found);
                row = row.erase(0, found + 1);

                //gets the string from the value
                if(valStr.compare(CLIENT_BORDER) == 0) {
                        val = graph::Graph::BORDER;
                }else{
                        try {
                                val = std::stod(valStr);
                        } catch(const std::exception& e){
                                out->writeOneMassege(SocketOStream::NO_RESPONSE,
                                         SocketOStream::INVALID_MATRIX_VALUE);
                                VALUE_ERROR;
                        }

                        if(val <= 0) {
                                out->writeOneMassege(SocketOStream::NO_RESPONSE,
                                         SocketOStream::VALUE_MUST_BE_POSITIVE);
                                VALUE_IS_NOT_POSITIVE;
                        }
                }

                if(valLoc >= matrix->getWidth()){//check for good index
                        out->writeOneMassege(SocketOStream::NO_RESPONSE,
                                 SocketOStream::NUM_VALUES_NOT_EQUALS_MATRIX_WIDTH);
                        NUM_VALUES_ERROR;
                }

                //puts the value in the matrix
                matrix->setValue(rowIndex, valLoc, val);
                found = row.find_first_of(",");
                ++valLoc;
                
        }

        //check the num of values in the row
        if(valLoc != matrix->getWidth()){
                out->writeOneMassege(SocketOStream::NO_RESPONSE,
                         SocketOStream::NUM_VALUES_NOT_EQUALS_MATRIX_WIDTH);
                NUM_VALUES_ERROR;
        }
}

std::vector<std::uint32_t> GraphProblemHandler::getTwoValueRaw(std::string row, SocketOStream* out) const {

        //find the "," index that is between the vlues
        std::size_t found = row.find_first_of(",");
        if(found == std::string::npos || (found + 1 == row.size())) {
                out->writeOneMassege(SocketOStream::NO_RESPONSE,
                         SocketOStream::MISSING_ROW_WITH_TWO_VALUES);
                ROW_WITH_TWO_VALUES_MISSING;
        }

        //gets the values
        std::uint32_t val1, val2;
        try {
                val1 = std::stoi(row.substr(0, found));
                val2 = std::stoi(row.substr(found + 1));
        } catch(const std::exception& e){
                out->writeOneMassege(SocketOStream::NO_RESPONSE,
                         SocketOStream::NO_INT_ROW_WITH_TWO_VALUES);
                INT_ROW_WITH_TWO_VALUES;
        }

        //puts the values in a vector
        std::vector<std::uint32_t> values;
        values.push_back(val1);
        values.push_back(val2);

        return values;
}

void GraphProblemHandler::handleProblem(std::unique_ptr<SocketIStream> in,
        std::unique_ptr<SocketOStream> out, std::string alg) const {
                //getting the solution
                auto graphSolution = std::move(getSolution(out.get(), alg));
                
                //geting the problem massege
                std::string problemStr = in->readOneMassege();

                //removing the spaces
                problemStr.erase(remove_if(problemStr.begin(), problemStr.end(), [](char c)
                              { return c == SPACE_CHAR; }), problemStr.end());

                //geting the problem
                
                //getting the matrix size
                std::vector<std::uint32_t> matrixSize = 
                        getTwoValueRaw(getNextRow(problemStr, out.get()), out.get());
                
                std::uint32_t height = matrixSize.front();
                std::uint32_t width = matrixSize.back();

                //getting the matrix
                std::unique_ptr<matrix::MatrixClass> matrix = 
                        std::make_unique<matrix::MatrixClass>(height, width);

                for(std::uint32_t i = 0; i < height; ++i) {
                        getMatixRaw(getNextRow(problemStr,
                                 out.get()), out.get(), matrix.get(), i);
                }

                //geting the start point
                std::vector<std::uint32_t> start = 
                        getTwoValueRaw(getNextRow(problemStr, out.get()), out.get());

                std::uint32_t xStart = start.front();
                std::uint32_t yStart = start.back();

                //getting the end point
                std::vector<std::uint32_t> end = 
                        getTwoValueRaw(getNextRow(problemStr, out.get()), out.get());

                std::uint32_t xEnd = end.front();
                std::uint32_t yEnd = end.back();

                //creating the problem
                auto graphProblem = 
                        std::make_unique<solver::problem::MatrixGraphProblem>(matrix.get(),
                         xStart, yStart, xEnd, yEnd);

                //creating the solver
                std::unique_ptr<solver::Solver> solver =
                         std::make_unique<solver::Solver>(graphProblem.get(),
                          graphSolution.get());

                //try to solve the problem
                out->writeOneMassege(solver->getStringSolution());
                //wirting to log server file -success
                std::string contant = 
                        files::readFileContent(SocketServer::LOG_LOCATION);
                files::writeFileContent(SocketServer::LOG_LOCATION,
                         contant + SUCCESS_MASSEGE);
     }

     std::string GraphProblemHandler::getNextRow(std::string& massege, SocketOStream* out) const {

                auto rowSize = massege.find_first_of(END_ROW);
                if(rowSize == std::string::npos) {
                        out->writeOneMassege(SocketOStream::NO_RESPONSE,
                                 SocketOStream::MISSING_ROW);
                        MISSING_ROW_ERROR;
                }
                std::string row = massege.substr(0, rowSize);

                //earsing the row drom the massege
                massege.erase(0, rowSize + END_ROW_NUM);

                return row;
     }