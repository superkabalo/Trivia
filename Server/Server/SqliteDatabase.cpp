#include "SqliteDatabase.h"
#include "Constants.h"
#include <random>
#include "Question.h"
#include <vector>
#include "LoggedUser.h"
#include <string>
#include <set>
// ignore irrelevant warning
#pragma warning(disable : 4996)

SqliteDatabase& SqliteDatabase::getInstance()
{
	static SqliteDatabase instance;	 // create SqliteDatabase instance which will be the only instance becuase it is static
	return instance;
}

bool SqliteDatabase::open()
{
	std::string dbFileName = "triviaDB.sqlite";
	const char* sqlStatement;
	char* errMessage = nullptr;
	int file_exist = _access(dbFileName.c_str(), 0);  // checking if the file exists
	int res = sqlite3_open(dbFileName.c_str(), &this->m_database);  // opening the database
	if (res != SQLITE_OK)
	{
		this->m_database = nullptr;
		throw std::exception("Failed to open DB");
		return false;
	}
	if (file_exist != FALSE)
	{	//  if the database file doesn't exist
		sqlStatement = "CREATE TABLE USERS (USER_NAME TEXT PRIMARY KEY NOT NULL, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL, ADDRESS TEXT NOT NULL, PHONE_NUMBER TEXT NOT NULL, BIRTH_DATE TEXT NOT NULL);";
		errMessage = nullptr;
		res = sqlite3_exec(m_database, sqlStatement, nullptr, nullptr, &errMessage);	// creating the users table
		if (res != SQLITE_OK)
		{
			this->m_database = nullptr;
			throw std::exception("SQLite ERROR");
			return false;
		}
		sqlStatement = "CREATE TABLE QUESTIONS ( QUESTION_ID INTEGER PRIMARY KEY AUTOINCREMENT , QUESTION TEXT NOT NULL, ANSWER1 TEXT NOT NULL, ANSWER2 TEXT NOT NULL, ANSWER3 TEXT NOT NULL, CORRECT_ANSWER TEXT NOT NULL);";//creating the questions table
		errMessage = nullptr;
		res = sqlite3_exec(m_database, sqlStatement, nullptr, nullptr, &errMessage);
		if (res != SQLITE_OK)
		{
			this->m_database = nullptr;
			throw std::exception("SQLite ERROR");
			return false;
		}
		// insert the questions into the database
		insertQuestion("In which year did the Franco-Prussian War end", "1865", "1898", "1935", "1871");
		insertQuestion("Who was the first englishman to partake in the trans-atlantic slave trade", "Francis Drake", "Winston Churchill", "Walter Raleigh", "John Hawkins");
		insertQuestion("Which one of these men conquerd England ", "Charlemagne", "Napoleon", "Gustavus Adolphus", "William of Normandy");
		insertQuestion("Who was the man who created the modern Germany ", "Wilhelm I", "Napoleon", "Leopold II", "Otto Von Bismarck");
		insertQuestion("Who was the first emperor of Rome ", "Charlemagne", "Romoulus", "Clovis", "Augustus");
		insertQuestion("Where was Alexander the Great Buried ", "Cairo", "Memphis", "Babylon", "Unknown");
		insertQuestion("Who was the head of the Confederacy of Delos ", "Macedonia", "Sparta", "Corinth", "Athens");
		insertQuestion("Who was the philosopher emperor ", "Tiberius", "Nero", "Caraclla", "Marcus Aurelius");
		insertQuestion("Which country did Gustavus Adolphus rule ", "Germany", "Austria", "Britain", "Sweden");
		insertQuestion("Who was the pope who called for the first crusade ", "Pius II", "Leo III", "Benedict IV", "Urban II");
		// create statistics table
		sqlStatement = "CREATE TABLE STATISTICS (USER_NAME TEXT NOT NULL, TOTAL_ANSWERS INT NOT NULL, CORRECT_ANSWERS INT NOT NULL, SCORE INT  NOT NULL, AVERAGE_ANSWER_TIME INT NOT NULL, NUM_OF_GAMES INT NOT NULL, FOREIGN KEY(USER_NAME) REFERENCES USERS(USER_NAME));";//creating the statistics table
		errMessage = nullptr;
		res = sqlite3_exec(m_database, sqlStatement, nullptr, nullptr, &errMessage);
		if (res != SQLITE_OK)
		{
			this->m_database = nullptr;
			throw std::exception("SQLite ERROR");
			return false;
		}
	}
	return true;
}

bool SqliteDatabase::close()
{
	int res = sqlite3_close(this->m_database);	// close the database
	if (res != SQLITE_OK)
	{
		this->m_database = nullptr;
		throw std::exception("Failed to close DB");
		return false;
	}
	this->m_database = nullptr;
	return true;
}

void SqliteDatabase::insertQuestion(const std::string& question, const std::string& firstAns, const std::string& secondAns, const std::string& thirdAns, const std::string& correctAns)
{
	const char* sqlStatement;
	char* errMessage = nullptr;
	int res;
	std::string temp = "INSERT INTO QUESTIONS (QUESTION, ANSWER1, ANSWER2,ANSWER3,CORRECT_ANSWER) VALUES(\"" + question + " \",\"" + firstAns + "\",\"" + secondAns + "\",\"" + thirdAns + "\",\"" + correctAns + "\");";
	sqlStatement = temp.c_str();
	res = sqlite3_exec(m_database, sqlStatement, nullptr, nullptr, &errMessage);  // insert question into the database
	if (res != SQLITE_OK)
	{
		this->m_database = nullptr;
		throw std::exception("SQLite ERROR");
	}
}

int SqliteDatabase::doesUserExistCallback(void* data, int argc, char** argv, char** azColName)
{
	int* returnValue = (int*)data;
	*returnValue = argc;	// set *returnValue as the number of arguments received - 0 or 1
	return 0;
}

int SqliteDatabase::doesUserExist(const std::string& username)
{
	int exists = FALSE;
	std::string temp = "SELECT USER_NAME FROM USERS WHERE USER_NAME = \"" + username + "\";";
	const char* sqlStatement = temp.c_str();
	char* errMessage = nullptr;
	int res = sqlite3_exec(m_database, sqlStatement, doesUserExistCallback, &exists, &errMessage);		// check if there is a user with the given username in the database
	if (res != SQLITE_OK)
	{
		// throw exception
		throw std::exception("SQLite error");
	}
	return exists;
}

int SqliteDatabase::getQuestionsCallback(void* data, int argc, char** argv, char** azColName)
{
	std::list<Question>* questionList = (std::list<Question>*)data;
	std::vector <std::string> possibleAnswers;
	// read the possible answerrs from the database
	std::string ans1 = argv[ANSWER_1_INDEX + INC];
	possibleAnswers.push_back(ans1);
	std::string ans2 = argv[ANSWER_2_INDEX + INC];
	possibleAnswers.push_back(ans2);
	std::string ans3 = argv[ANSWER_3_INDEX + INC];
	possibleAnswers.push_back(ans3);
	std::string ans4 = argv[ANSWER_4_INDEX + INC];
	possibleAnswers.push_back(ans4);

	// Create the Question object with the question text and possible answers
	std::string questionText = argv[QUESTION_INDEX + INC];
	Question temp(questionText, possibleAnswers);// initiate the question with the question and the possible answers
	questionList->push_back(temp);		// add the question to the questions list
	return 0;
}

int SqliteDatabase::getIntegerFromDBCallback(void* data, int argc, char** argv, char** azColName)
{
	int* num = (int*)data;
	if (argc > EMPTY)	// no results precaution
	{
		*num = std::stoi(argv[0]);;	// set *num as the first and only integer returned
	}
	return 0;
}

int SqliteDatabase::getHighScoreCallback(void* data, int argc, char** argv, char** azColName)
{
	std::vector<std::string>* scoreList = (std::vector<std::string>*)data;
	if (argc > EMPTY)
	{
		scoreList->push_back((std::string)*argv);	// adding the name of the user and his score to the score list vector
		scoreList->push_back(std::to_string(SqliteDatabase::getInstance().getPlayerScore(scoreList->back())));
	}

	return 0;
}

int SqliteDatabase::getAverageAnswerTimeCallback(void* data, int argc, char** argv, char** azColName)
{
	int* answerTime = (int*)(data);
	std::string temp;
	if (argc > EMPTY)
	{
		temp = *argv;
		*answerTime = std::stof(temp); // assigning the given answer time to the value in answerTime
	}
	return 0;
}
int SqliteDatabase::submitGameStatistics(const GameData& gameData, const LoggedUser& user)
{
	char* errMessage = nullptr;
	int score = gameData.correctAnswerCount;  // calculate the user's score (correctAnswers / wrongAnswers)
	if (gameData.wrongAnswerCount != EMPTY)
	{
		score = gameData.correctAnswerCount / gameData.wrongAnswerCount;
	}
	std::string temp = "UPDATE STATISTICS SET TOTAL_ANSWERS = TOTAL_ANSWERS + " + std::to_string(gameData.correctAnswerCount + gameData.wrongAnswerCount) + ", CORRECT_ANSWERS = CORRECT_ANSWERS + " + std::to_string(gameData.correctAnswerCount) + ", SCORE= SCORE +" + std::to_string(score) + ", AVERAGE_ANSWER_TIME=" + std::to_string(gameData.averageAnswerTime) + ", NUM_OF_GAMES = NUM_OF_GAMES + 1 WHERE USER_NAME == \"" + user.getUsername() + "\";";
	const char* sqlStatement = temp.c_str();
	int res = sqlite3_exec(m_database, sqlStatement, nullptr, nullptr, &errMessage);  // update statistics data accordingly
	if (res != SQLITE_OK)
	{
		// throw exception
		throw std::exception("SQLite error");
	}
	return (int)true;
}
int SqliteDatabase::doesPasswordMatch(const std::string& username, const std::string& password)
{
	std::string userPassword;
	std::string temp = "SELECT PASSWORD FROM USERS WHERE USER_NAME=\"" + username + "\";";
	const char* sqlStatement = temp.c_str();
	char* errMessage = nullptr;
	int res = sqlite3_exec(m_database, sqlStatement, doPasswordsMatchCallback, &userPassword, &errMessage);  // get user password from the database
	if (res != SQLITE_OK)
	{
		// throw exception
		throw std::exception("SQLite error");
	}
	return userPassword == password;  // check if password from the database is the same as the given password
}

int SqliteDatabase::addNewUser(const std::string& username, const std::string& password, const std::string& email, const std::string& address, const std::string& phoneNumber, const std::string& birthDate)
{
	std::string temp = "INSERT INTO USERS (EMAIL,USER_NAME,PASSWORD,ADDRESS,PHONE_NUMBER,BIRTH_DATE) VALUES(\"" + email + "\" , \"" + username + "\", \"" + password + "\", \"" + address + "\", \"" + phoneNumber + "\", \"" + birthDate + "\");";  // inserting the given email, username and password into the table
	const char* sqlStatement = temp.c_str();
	char* errMessage = nullptr;
	int res = sqlite3_exec(m_database, sqlStatement, nullptr, nullptr, &errMessage);	// insert the user's details into the users table
	if (res != SQLITE_OK)
	{
		// throw exception
		throw std::exception("SQLite error");
	}
	temp = "INSERT INTO STATISTICS (USER_NAME,TOTAL_ANSWERS, CORRECT_ANSWERS, SCORE, AVERAGE_ANSWER_TIME, NUM_OF_GAMES) VALUES(\"" + username + "\",0,0,0,0.0,0); ";  // inserting the given email, username and password into the table
	sqlStatement = temp.c_str();
	errMessage = nullptr;
	res = sqlite3_exec(m_database, sqlStatement, nullptr, nullptr, &errMessage);	// insert the user into the statistics table
	if (res != SQLITE_OK)
	{
		// throw exception
		throw std::exception("SQLite error");
	}
	return true;
}
std::vector<std::string> SqliteDatabase::getHighScores()
{
	std::vector<std::string> highestScores;
	const char* sqlStatement = "SELECT USER_NAME FROM STATISTICS ORDER BY SCORE DESC LIMIT 3;";  // asking the data base for the 3 users whose scores are the highest
	char* errMessage = nullptr;
	int res = sqlite3_exec(m_database, sqlStatement, &getHighScoreCallback, &highestScores, &errMessage);	// get the names of the 3 highest scorers
	if (res != SQLITE_OK)
	{
		// throw exception
		throw std::exception("SQLite error");
	}
	return highestScores;
}
int SqliteDatabase::doPasswordsMatchCallback(void* data, int argc, char** argv, char** azColName)
{
	std::string* password = (std::string*)data;
	for (int i = EMPTY; i < argc; i++)
	{
		if (!strcmp(azColName[i], PASSWORD))
		{	// save the found password
			*password = std::string(argv[i]);
		}
	}
	return 0;
}
std::list<Question> SqliteDatabase::getQuestions(const int numOfQuestions)
{
	int min = START_OF_RANGE;
	int max = NUM_OF_QUESTIONS;

	// create a random device and seed the generator
	std::random_device rd;
	std::mt19937 gen(rd());
	std::set<int> random_numbers;
	// create a uniform distribution in the range [min, max]
	std::uniform_int_distribution<> dis(min, max);
	int randomNumber = 0;
	int temp = 0;
	std::list<Question> questionList;
	while (random_numbers.size() < numOfQuestions)  // generate numOfQuestion different number
	{
		randomNumber = dis(gen);  // generate new number
		if (random_numbers.find(randomNumber) != random_numbers.end())  // check if the number already is in the set
		{
			continue;
		}
		random_numbers.insert(randomNumber);  // insert the number to the set
		std::string temp = "SELECT * FROM QUESTIONS WHERE QUESTION_ID == " + std::to_string(randomNumber) + ";";
		const char* sqlStatement = temp.c_str();
		char* errMessage = nullptr;
		int res = sqlite3_exec(m_database, sqlStatement, getQuestionsCallback, &questionList, &errMessage);  // get the curren question
		if (res != SQLITE_OK)
		{
			// throw exception
			throw std::exception("SQLite error");
		}
	}
	return questionList;
}

int SqliteDatabase::getPlayerAverageAnswerTime(const std::string& username)
{
	int averageAnswerTime = EMPTY;
	std::string temp = "SELECT AVERAGE_ANSWER_TIME FROM STATISTICS WHERE USER_NAME=\"" + username + "\";";  //asking the database for the user's average answer time
	const char* sqlStatement = temp.c_str();
	char* errMessage = nullptr;
	int res = sqlite3_exec(m_database, sqlStatement, getAverageAnswerTimeCallback, &averageAnswerTime, &errMessage);  // get the user's average answering time from the database
	if (res != SQLITE_OK)
	{
		// throw exception
		throw std::exception("SQLite error");
	}
	return averageAnswerTime;
}

int SqliteDatabase::getNumOfCorrectAnswers(const std::string& username)
{
	int num = EMPTY;
	std::string temp = "SELECT CORRECT_ANSWERS FROM STATISTICS WHERE USER_NAME=\"" + username + "\";";  //asking the database for the user's num of correct answers
	const char* sqlStatement = temp.c_str();
	char* errMessage = nullptr;
	int res = sqlite3_exec(m_database, sqlStatement, getIntegerFromDBCallback, &num, &errMessage);  // get the user's num of correct answers from the database
	if (res != SQLITE_OK)
	{
		// throw exception
		throw std::exception("SQLite error");
	}
	return num;
}

int SqliteDatabase::getNumOfTotalAnswers(const std::string& username)
{
	int num = 0;
	std::string temp = "SELECT TOTAL_ANSWERS FROM STATISTICS WHERE USER_NAME=\"" + username + "\";";  //asking the database for the user's num of total answers
	const char* sqlStatement = temp.c_str();
	char* errMessage = nullptr;
	int res = sqlite3_exec(m_database, sqlStatement, getIntegerFromDBCallback, &num, &errMessage);  // get user's num of total answers from the database
	if (res != SQLITE_OK)
	{
		// throw exception
		throw std::exception("SQLite error");
	}
	return num;
}

int SqliteDatabase::getNumOfPlayerGames(const std::string& username)
{
	int num = 0;
	std::string temp = "SELECT NUM_OF_GAMES FROM STATISTICS WHERE USER_NAME=\"" + username + "\";";  //asking the database for the num of the user's games
	const char* sqlStatement = temp.c_str();
	char* errMessage = nullptr;
	int res = sqlite3_exec(m_database, sqlStatement, getIntegerFromDBCallback, &num, &errMessage);  // get num of user's games
	if (res != SQLITE_OK)
	{
		// throw exception
		throw std::exception("SQLite error");
	}
	return num;
}

int SqliteDatabase::getPlayerScore(const std::string& username)
{
	int num = 0;
	std::string temp = "SELECT MAX(SCORE) FROM STATISTICS WHERE USER_NAME=\"" + username + "\";";  //selecting the user's best score
	const char* sqlStatement = temp.c_str();
	char* errMessage = nullptr;
	int res = sqlite3_exec(m_database, sqlStatement, getIntegerFromDBCallback, &num, &errMessage);  // get user's highest score from the database
	if (res != SQLITE_OK)
	{
		// throw exception
		throw std::exception("SQLite error");
	}
	return num;
}