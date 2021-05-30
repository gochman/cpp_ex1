//
// Created by Yoav Gochman, id 205530983 on 14/01/2020.
//

#include "HashMap.hpp"
#include <iostream>
#include <regex>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <fstream>

#define INVALID_INPUT_MSG "Invalid input"
#define USAGE_ERR_MSG "Usage: SpamDetector <database path> <message path> <threshold>"
#define LEGAL_INPUT_REGEX "^(.+),(\\d+)$"

using namespace std;

/*
 *   ******** Parser ********
 */

/**
 * @brief Helper class that parses the CSV file and generates a HashMap
 */
class CSVParser
{
public:

    /**
     * @brief constructor
     * @param path path to file
     */
    explicit CSVParser(string path)
    {
        _path = path;
    }

    /**
     * @brief file validate
     * @return true if the files is in the right format
     */
    int fileValidate()
    {

        ifstream file(_path);

        if (file.fail())
        {
            file.close();
            return EXIT_FAILURE;
        }


        if (file.is_open())
        {
            std::string line;
            while (getline(file, line))
            {
                // strip line from new lines
                boost::replace_all(line, "\r", "");
                boost::replace_all(line, "\n", "");

                // validate there is only 1 comma
                int delimiterCounter = 0;
                string delimiter = ",";
                for (size_t offset = line.find(delimiter); offset != std::string::npos;
                     offset = line.find(delimiter, offset + delimiter.length()))
                {
                    delimiterCounter += 1 ;
                }

                regex re(LEGAL_INPUT_REGEX);
                if (!regex_match(line, re) || delimiterCounter != 1)
                {
                    file.close();
                    return EXIT_FAILURE;

                }
            }
        }

        file.close();
        return EXIT_SUCCESS;
    }


    /**
     * @brief The parser products, HashMap representing <phrase, score>
     * @return HashMap pointer
     */
    HashMap<string, int> *generateScoreMap()
    {

        auto result = new HashMap<string, int>;
        std::ifstream file(_path);

        if (file.is_open())
        {
            std::string line;
            while (getline(file, line))
            {
                boost::replace_all(line, "\r", "");
                boost::replace_all(line, "\n", "");

                regex re(LEGAL_INPUT_REGEX);
                smatch match;

                if (regex_search(line, match, re))
                {
                    string phrase;
                    int score;
                    // convert to lowercase
                    phrase = boost::algorithm::to_lower_copy(match.str(1));
                    score = boost::lexical_cast<int>(match.str(2));

                    (*result).insert(phrase, score);
                }

            }
        }

        file.close();
        return result;


    }

private:

    string _path;


};

/**
 * @brief Helper class that parses the Text file and generates a HashMap
 */
class TextParser
{
private:
    string _textFile;

public:
    /**
     * @brief constructor
     * @param textFilePath a path to read
     */
    explicit TextParser(string textFilePath) :
            _textFile(textFilePath)
    {
    }

    /**
     * @brief Helper function that validated the file is available (can be empty)
     * @return
     */
    int fileValidate()
    {

        ifstream file(_textFile);

        if (file.fail())
        {
            return EXIT_FAILURE;
        }


        return EXIT_SUCCESS;

    }

    /**
     * @brief product of this parser, returns an appearance map relevant to the keys in scoreMap
     * @param scoreMap keys to copy
     * @return hashMap of <phrase,times appeared>
     */
    HashMap<string, int> *generateAppearanceMap(HashMap<string, int> *scoreMap)
    {
        auto result = new HashMap<string, int>(*scoreMap); // hard copy
        (*result).setValuesToDefault(); // in this case all values will be 0;

        std::ifstream file(_textFile);

        if (file.is_open())
        {
            std::string line;
            while (getline(file, line))
            {
                // strip line from new lines and lower
                boost::replace_all(line, "\r", "");
                boost::replace_all(line, "\n", "");
                boost::algorithm::to_lower(line);
                for (auto const &pair:(*scoreMap))
                {
                    string key = pair.first;
                    for (size_t offset = line.find(key); offset != std::string::npos;
                         offset = line.find(key, offset + key.length()))
                    {
                        int cur_score = (*result).at(key);
                        (*result)[key] = cur_score + 1;

                    }

                }
            }
        }

        file.close();

        return result;


    }
};

/**
 * @brief Main helper: check validity of parsed files
 * @param csvParser csv Parser
 * @param txtParser txt Parser
 * @return SUCCESS if the files are ok and ready to generate maps
 */
int validateFilesHelper(CSVParser& csvParser,TextParser &txtParser){
    int csvVal = csvParser.fileValidate();
    if (csvVal == EXIT_FAILURE){
        return EXIT_FAILURE;
    }

    int txtVal = txtParser.fileValidate();
    if (txtVal == EXIT_FAILURE){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}

/**
 * @brief gets scoreMap and appearanceMap and generates a TOTAL score. (sum of (phraseScore *
 * scoreAppearance)
 * @param scoreMap a score HashMap
 * @param appearanceMap an appearances HashMap
 * @return integer reprsenting total Score
 */
int totalTextScore(HashMap<string, int> *scoreMap, HashMap<string, int> *appearanceMap)
{
    int sum = 0;
    for (auto const &pair: *appearanceMap)
    {
        string phrase = pair.first;
        int score = (*scoreMap).at(phrase);
        int appearances = (*appearanceMap).at(phrase);
        sum += (score * appearances);
    }

    return sum;
}

/**
 * @brief Helper function that validated the threshold input (should be positive int)
 * @param thresholdInput a string representing the threshold
 * @return minus EXIT FAILURE if there is a problem. a positive integer otherwise representing
 * the converted int.
 */
int validateThresholdInput(string thresholdInput)
{
    double result;
    try
    {
        result = stod(thresholdInput);
    }
    catch (exception &e)
    {
        return -EXIT_FAILURE;
    }

    if ((result <= 0) || (trunc(result) != result)){
        return -EXIT_FAILURE;

    }

    return result;

}

/**
 * @brief Helper function that prints the result
 * @param score gets a calculated total score
 * @param threshold the threshold to pass to be not_spam
 */
void printResult(int score, double threshold)
{
    if (score >= threshold)
    {
        cout << "SPAM" << endl;
    }
    else
    {
        cout << "NOT_SPAM" << endl;
    }
}

/**
 * @brief Main function
 * @param argc num of args
 * @param argv array of arguments
 * @return EXIT_SUCCESS on a successful calculation that generates SPAM / NOT_SPAM message
 */
int main(int argc, char *argv[])
{
    // First Validate num of arguments
    if (argc - 1 != 3)
    {
        cerr << USAGE_ERR_MSG << endl;
        return -EXIT_FAILURE;
    }

    // Create Parsers
    CSVParser myCSVParser(argv[1]);
    TextParser myTextParser(argv[2]);

    // Validate Input
    int validated = validateFilesHelper(myCSVParser,myTextParser);
    double threshold = validateThresholdInput(argv[3]);

    if (validated == EXIT_FAILURE || (threshold == -EXIT_FAILURE)){
        cerr << INVALID_INPUT_MSG << endl;
        return EXIT_FAILURE;
    }


    // Generate maps and print result
    auto scoreMap = myCSVParser.generateScoreMap();
    auto appearancesMap = myTextParser.generateAppearanceMap(scoreMap);
    int totalScore = totalTextScore(scoreMap, appearancesMap);
    printResult(totalScore, threshold);



    delete scoreMap;
    delete appearancesMap;


}