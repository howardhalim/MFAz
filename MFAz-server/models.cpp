#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <memory>
#include <cppcms/json.h>

#include <optional>

#define DB_NAME "gateway"  //set DB name here
#define DB_USERNAME "root" //default user
#define DB_PASSWORD "12345" //default password set it accordingly
#define DB_HOST "tcp://127.0.0.1:3306" //default port on localhost

using namespace std;

class GrantedAccess{
private:
    sql::mysql::MySQL_Driver *driver;
    unique_ptr<sql::Connection> con;
    unique_ptr<sql::PreparedStatement> stmt;

public:
    GrantedAccess() {
        try {
            driver = sql::mysql::get_mysql_driver_instance();
            con.reset(driver->connect(DB_HOST, DB_USERNAME, DB_PASSWORD));
            con->setSchema(DB_NAME);
        } catch (sql::SQLException &e) {
            cerr << "SQLException: " << e.what() << endl;
        } catch (...) {
            cerr << "Unexpected error during connection" << endl;
        }
    }

    // Method to insert a record into the granted_access table
    void insert_access(int userId, const string &access) {
        try {
            stmt.reset(con->prepareStatement("INSERT INTO granted_access(user_id, granted_access) VALUES (?, ?)"));
            stmt->setInt(1, userId);
            stmt->setString(2, access);
            stmt->executeUpdate();
            cout << "Access granted successfully!" << endl;
        } catch (sql::SQLException &e) {
            cerr << "SQLException: " << e.what() << endl;
        } catch (...) {
            cerr << "Unexpected error during insertion" << endl;
        }
    }

    // Method to retrieve records from the granted_access table
    vector<string> get_access(int userId) {
        vector<string> accessList;
        try {
            stmt.reset(con->prepareStatement("SELECT granted_access FROM granted_access WHERE user_id = ?"));
            stmt->setInt(1, userId);
            unique_ptr<sql::ResultSet> result(stmt->executeQuery());
            while (result->next()) {
                string granted_access = result->getString("granted_access");
                accessList.push_back(granted_access);
            }
        } catch (sql::SQLException &e) {
            cerr << "SQLException: " << e.what() << endl;
        } catch (...) {
            cerr << "Unexpected error during retrieval" << endl;
        }
        return accessList;
    }
    


    pair <bool, optional<int>> login_verification(const string &username, const string &password) {
        try {
            stmt.reset(con->prepareStatement("SELECT user_id, password FROM account WHERE username = ?"));
            stmt->setString(1, username);
            unique_ptr<sql::ResultSet> result(stmt->executeQuery());

            if (result->next()) {
                string stored_password = result->getString("password");
                int user_id = result -> getInt("user_id");

                // For better security, hash the password and compare the hashed versions, as a demo a non encrypted password is used
                if (stored_password == password) { // In real applications, use a hashed comparison!
                    cout << "Login successful!" << endl;
                    return {true,user_id};
                }
            }

            cout << "Invalid username or password!" << endl;
            return {false, std::nullopt};
        } catch (sql::SQLException &e) {
            cerr << "SQLException: " << e.what() << endl;
            return {false, std::nullopt};
        } catch (...) {
            cerr << "Unexpected error during login verification" << endl;
            return {false, std::nullopt};
        }
    }

    bool register_user(const string &username, const string &password, int userid) {
        try {
            // Check if the username already exists
            stmt.reset(con->prepareStatement("SELECT COUNT(*) FROM account WHERE username = ?"));
            stmt->setString(1, username);
            unique_ptr<sql::ResultSet> result(stmt->executeQuery());

            if (result->next() && result->getInt(1) > 0) {
                cout << "Username already exists!" << endl;
                return false;
            }
            // Insert new user into the account table
            stmt.reset(con->prepareStatement("INSERT INTO account (username, password, user_id) VALUES (?, ?, ?)"));
            stmt->setString(1, username);
            stmt->setString(2, password);
            stmt->setInt(3,userid);
            stmt->executeUpdate();

            cout << "Registration successful!" << endl;
            return true;
        } catch (sql::SQLException &e) {
            cerr << "SQLException: " << e.what() << endl;
            return false;
        } catch (...) {
            cerr << "Unexpected error during registration" << endl;
            return false;
        }
    }

    void create_session(int userId, const string &sessionId) {
        try {
            stmt.reset(con->prepareStatement("INSERT INTO session(user_id, session_id) VALUES (?, ?)"));
            stmt->setInt(1, userId);
            stmt->setString(2, sessionId);
            stmt->executeUpdate();
            std::cout << "Session created successfully!" << std::endl;
        } catch (sql::SQLException &e) {
            std::cerr << "SQLException: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Unexpected error during session creation" << std::endl;
        }
    }

    int get_id_from_sessionid(const string &sessionId){
        int userId = -1; // Default value indicating "not found"
        try {
            // Prepare the SQL statement to select user_id based on session_id
            stmt.reset(con->prepareStatement("SELECT user_id FROM session WHERE session_id = ?"));
            stmt->setString(1, sessionId);
            
            // Execute the query
            std::unique_ptr<sql::ResultSet> result(stmt->executeQuery());

            // Check if a result was returned
            if (result->next()) {
                userId = result->getInt("user_id"); // Get the user_id
            } else {
                std::cout << "Session ID not found!" << std::endl;
            }
        } catch (sql::SQLException &e) {
            std::cerr << "SQLException: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Unexpected error during session retrieval" << std::endl;
        }
        
        return userId; // Return the user_id (or -1 if not found)
    }
};