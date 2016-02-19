// =============================================================================
//! \file
//! \brief          Requirements
//! \author         Norbert Toth
//! \date           08.02.2016.
//! \note
// =============================================================================
//!
//! \page requirements Requirements
//! \tableofcontents
//! \section feature Features
//!
//! -# <div id="FT001"><b>FT001:</b> I, as a web-service client want to communicate in a full-duplex manner to the server via a secure channel.<br>
//! <b>Acceptance criteria:</b> The applied communication protocol is secure web socket(wss) or HTTPS that use TLS.</div>
//!
//! -# <div id="FT002"><b>FT002:</b> I, as an unauthenticated web-service client want to sign in into the server by my username and password.<br>
//! <b>Acceptance criteria:</b> The client sends its username and password. If they identify a registered user and are valid, the server
//! allow the client to log in.</div>
//!
//! -# <div id="FT003"><b>FT003:</b> I, as an unauthenticated and unregistered web-service client want to register on the server.<br>
//! <b>Acceptance criteria:</b> The client sends username, password and email address to the server via HTTPS POST. The registration
//! is success if the username and password isn't already used on the server.</div>
//!
//! -# <div id="FT004"><b>FT004:</b> I, as an authenticated web-service client want to get the list of registered users.<br>
//! <b>Acceptance criteria:</b> The client sends an HTTPS GET and the response contains the username of registered users. The reply
//! is empty only if there is no users registered on the server.</div>
//!
//! -# <div id="FT005"><b>FT005:</b> I, as an authenticated web-service client want to get notification about the state change of the clients.<br>
//! <b>Acceptance criteria:</b> The client receives notification if the state of another users changed. The granularity of notifications
//! is one user.</div>
//!
//! -# <div id="FT006"><b>FT006:</b> I, as an authenticated web-service client want to send both of text messages and files to my conversation partner.<br>
//! <b>Acceptance criteria:</b> The client sends HTTPS POST to the server that persists the message or file. If everything was successful,
//! the conversation partner receives a notification.</div>
//!
//! -# <div id="FT007"><b>FT007:</b> I, as an authenticated web service client want to get the list of former conversations.<br>
//! <b>Acceptance criteria:</b> The client sends HTTPS GET to the server. The response response holds the list of conversations.
//! The detailed conversation could be acquired by separate HTTPS GET.</div>
//!
//! -# <div id="FT008"><b>FT008:</b> I, as an authenticated web service client want to be able to store arbitrary size and count of configuration data on the
//! server concerning to my client side application.<br>
//! <b>Acceptance criteria:</b> The client uses HTTPS POST to create or modify configuration data and DELETE for removing existing one.</div>
//!
//! \section userstory User stories
//!
//! -# <div id="US001"><b>US001:</b><br>
//! <b>Affected features:</b> <a href="#FT001">FT001</a><br>
//! </div>
//!
//! -# <div id="US002"><b>US002:</b> Request authentication<br>
//! <b>Affected features:</b> <a href="#FT002">FT002</a><br>
//! The web-service listens on the default HTTPS port (443). This can be changed by configuration. Considering the stateless manner of the HTTPS
//! protocol, the client shall send the username and password every time if it uses HTTPS verbs or one time if it opens a web-socket.</div>
//!
//! -# <div id="US003"><b>US003:</b> Configuration management<br>
//! <b>Affected features:</b> <a href="#FT002">FT002</a>, <a href="#FT008">FT008</a><br>
//! Configuration data falls into to classes: the user and the server configuration data. While the user is allowed to change its data as it wants,
//! the server side configuration is read-only and the server administrator has exclusive right to change them. From the webservice point of view both
//! kind of data are constant.<br>
//!     -# Server configuration consist of two parts:
//!         -# The configuration manager that is a software component and exists in the system as the single point to access configuration file. If the
//!             required configuration data isn't in the configuration file, the configuration manager is responsible to provide a default value.
//!         -# The configuration file that holds data in key-value pairs representation.
//!         .
//!     -# Client configuration data management:<br>
//!     Client configuration data belongs to the specific user and takes place within the configuration table of the user. For details see
//!     <a href="#configuration_data">user configuration table</a>. The webservice client allowed to create new or update an existent configuration item
//!     by the following request:
//!     \code
//!     POST https://<server_URL>[optional_port]/<username>/configuration
//!     Content-Type: application/json
//!     {
//!     "key_0": "value_0",
//!     "key_1": "value_1",
//!     "key_n": "value_n",
//!     }
//!     \endcode
//!     The operation can result the following error codes:
//!         -# <b>200 OK: </b>Everything went fine, and there were no new item
//!         -# <b>201 Created: </b>Everything went fine, but at least one key was new to the database. The new keys are listed in the body of the response
//!         -# <b>400 Bad Request: </b>Unknown error occured
//!         -# <b>401 Unauthorized: </b>The request tried to access resource that is forbidden for it
//!         .
//!     If the client wants to delete item (e.g.: its not needed anymore), then it can be done by sending a DELETE request:
//!     \code
//!     POST https://<server_URL>[optional_port]/<username>/configuration/<key_to_be_deleted>
//!     \endcode
//!     The operation result is <b>200 OK</b> in every cases.
//!
//!  </div>
//!
//! -# <div id="US004"><b>US004:</b> Create user account<br>
//! <b>Affected features:</b> <a href="#FT003">FT003</a><br>
//! Client registration has been done via the following HTTPS request:<br>
//! \code
//! POST https://<server_URL>[optional_port]/register
//! Content-Type: application/json
//! {
//! "username": "some",
//! "password": "pwd",
//! "email": "emailaddress"
//! }
//! \endcode
//! <br>
//! The password:
//!     -# Must be at least 8 long
//!     -# Must include numbers, lowercase and uppercase letters
//!     .
//! The username:
//!     -# Is between 6 and 256 characters
//!     -# Starts with letter
//!     -# Including numerical characters is allowed
//!     .
//! If these requirements are fulfilled, the web-server tries to append a new record into the user table. The user table uses the
//! the user and password columns for primary key. Due to security reasons, only the hash of password is stored. Both column is fixed size character
//! represented, and the size is derived from the maximal length of the username and the output size of the SHA512 algorithm. The email
//! address also stored in a text column and a regexp should check whether it contains the '@' and '.' characters.<br>
//! Depend on the success of the user account creation, the client receives the following error codes:
//!     -# <b>201 Created: </b>Everything went fine, the user credential is active and the user now can log in.
//!     -# <b>400 Bad Request: </b>One or more argument of the registration is not fulfill the required form.
//!     -# <b>409 Conflict: </b>There is an user already registered with the same username and password.
//!     .
//! </div>
//!
//! -# <div id="US005"><b>US005:</b> Database<br>
//! <b>Depends on user stories:</b> </a><br>
//! <b>Affected features:</b> <a href="#FT003">FT003</a>, <a href="#FT008">FT008</a><br>
//! The Chat based on PostgreSQL database and uses of the following tables:
//!     -# The "users" table is the most important one because it stores every necessary informations about the registered users. They are
//!         mandatory to register new users or authenticate an existent one. The table stores the following informations:
//!         -# <b>username: </b> 256 character max length, stores the username, part of the primary key
//!         -# <b>email: </b> 256 character max length, stores the email address of the user, part of the primary key
//!         -# <b>pwd: </b> 256 character max length, stores the SHA512 hash of the password
//!         .
//!     Creating the table has been done by the statement:<br>
//!     \code
//!     CREATE TABLE IF NOT EXISTS users(
//!         username VARCHAR(256),
//!         email VARCHAR(256) NOT NULL,
//!         pwd VARCHAR(256) NOT NULL,
//!         UNIQUE(email),
//!         PRIMARY KEY (username));
//!     \endcode
//!     -# <div id="configuration_data"> The table where the user can store its client side configuration data. Existence of the table is optional and depends on client side requirements.
//!     The table stores the following informations:
//!         -# <b>key: </b> The text represented key that the user uses to access the particular option
//!         -# <b>value: </b> The current configuration value
//!         .
//!     Creating the table has been done by the statement:<br>
//!     \code
//!     CREATE TABLE IF NOT EXISTS <username>.configuration<br> (
//!         key TEXT,
//!         value TEXT NOT NULL,
//!         PRIMARY KEY (key));
//!     \endcode
//!     </div>
//!     -# Assuming that the continuous usage of Chat produces lots of data, the conversations are splitted up into several tables. The naming convention
//!         of the table is CDDMMYYHHMMSS where:
//!         -# <b>C: </b> Starting letter of "Conversation"
//!         -# <b>DDMMYY: </b> Current date in UK format
//!         -# <b>HHMMSS: </b> Current time
//!         .
//!     The date and time information matches to the table creation date and time. Each of the conversation tables contain configurable number of rows.
//!     The default value is 1000000 rows and it can be overwritten via configuration file between 1 and 2^31 - 1. If the table reaches this row count, a
//!     new table will be created by the web-service. The table stores the following informations:
//!         -# <b>key: </b> Automincremented key for the conversation
//!         -# <b>time: </b> The date and time-stamp where the web-service receives the new conversation. The time-stamp holds the timezone information as well,
//!             that could be differ from the timezone of the message sender. In that case it's up to the client to recalculate the correct timezone.
//!         -# <b>message: </b> The next message in a conversation
//!         -# <b>user: </b> The author of the message
//!         .
//!     Creating the table has been done by the statement:<br>
//!     \code
//!     CREATE TABLE IF NOT EXISTS <CDDMMYYHHMMSS> (
//!         key SERIAL,
//!         time TIMESTAMP WITH TIME ZONE NOT NULL,
//!         message TEXT NOT NULL,
//!         user VARCHAR(256),
//!         FOREIGN KEY (user) REFERENCES users (username),
//!         PRIMARY KEY (key));
//!     \endcode
//!
//! </div>
//!
// =============================================================================
//! \file
//! \copyright
// ====================== end of file: requirements.hpp ========================
