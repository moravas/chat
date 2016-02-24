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
//! \section userstory User stories
//!
//! \subsection US001 US001: Conversation
//! <b>Affected features:</b> <a href="#FT006">FT006</a><br>
//! The process of the conversation between 2 particiapants can be splitted up to three parts regardless of the state of the participants:
//!     -# <b>Initiate conversation:</b>
//!     .
//!
//! \subsection US002 US002: Request authentication
//! <b>Affected features:</b> <a href="#FT002">FT002</a><br>
//! As an unauthenticated user, I'd like to sign in through the REST API by using HTTP POST in order to send my user name and password and receive 
//! an authentication token that will be used in the future requests.
//! The web-service listens on the default HTTPS port (443). This can be changed by configuration. Considering the stateless manner of the HTTPS
//! protocol, the client shall send the username and password every time if it uses HTTPS verbs or one time if it opens a web-socket.
//! 
//! \code
//! POST https://<server_URL>[optional_port]/login
//! Content-Type: application/json
//! {
//!   "username": "some",
//!   "password": "pwd",
//! }
//! \endcode
//! If the login is successful, the client receives the HTTP 200 OK response:
//! \code
//! Content-Type: application/json
//! {
//!   "token": "***TOKEN***",
//! }
//! \endcode
//! else the client receives the HTTP 401 Unauthorized.
//!
//! In the subsequent requests, the following additional header is included:
//! 
//! \code
//! X-Authentication-Token: ***TOKEN***
//! \endcode
//!
//! \subsection US003 US003: Configuration management
//! <b>Affected features:</b> <a href="#FT002">FT002</a>, <a href="#FT008">FT008</a><br>
//! Configuration data falls into to classes: the user and the server configuration data. While the user is allowed to change its data as it wants,
//! the server side configuration is read-only and the server administrator has exclusive right to change them. From the web-service point of view both
//! kind of data are constant.<br>
//!     -# Server configuration consist of two parts:
//!         -# The configuration manager that is a software component and exists in the system as the single point to access configuration file. If
//!             the required configuration data isn't in the configuration file, the configuration manager is responsible to provide a default value.
//!         -# The configuration file that holds data in key-value pairs representation.
//!         .
//!     -# Client configuration data management:<br>
//!     Client configuration data belongs to the specific user and takes place within the configuration table of the user. For details see
//!     <a href="#configuration_data">user configuration table</a>. The webservice client allowed to create new or update an existent configuration
//!     item by the following request:
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
//!         -# <b>200 OK:</b> Everything went fine, and there were no new item
//!         -# <b>201 Created:</b> Everything went fine, but at least one key was new to the database. The new keys are listed in the body of the response
//!         -# <b>400 Bad Request:</b> Unknown error occurred
//!         -# <b>401 Unauthorized:</b> The request tried to access resource that is forbidden for it
//!         .
//!     If the client wants to delete item (e.g.: its not needed anymore), then it can be done by sending a DELETE request:
//!     \code
//!     POST https://<server_URL>[optional_port]/<username>/configuration/<key_to_be_deleted>
//!     \endcode
//!     The operation result is <b>200 OK</b> in every cases.
//!
//! \subsection US004 US004: Create user account
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
//!
//! \subsection US005 US005: Database
//! <b>Depends on user stories:</b> </a><br>
//! <b>Affected features:</b> <a href="#FT003">FT003</a>, <a href="#FT008">FT008</a><br>
//! The Chat based on PostgreSQL database and uses of the following tables:
//!     -# The "users" table is the most important one because it stores every necessary informations about the registered users. They are
//!         mandatory to register new users or authenticate an existent one. The table stores the following informations:
//!         -# <b>username:</b> 256 character max length, stores the username, part of the primary key
//!         -# <b>email:</b> 256 character max length, stores the email address of the user, part of the primary key
//!         -# <b>pwd:</b> 256 character max length, stores the SHA512 hash of the password
//!         -# <b>logoff:</b> The last log off time of the user. Using it optional and can affect the client side operations
//!         .
//!     Creating the table has been done by the statement:
//!     \code
//!     CREATE TABLE users(
//!         username VARCHAR(256),
//!         email VARCHAR(256) NOT NULL,
//!         pwd VARCHAR(256) NOT NULL,
//!         logoff TIMESTAMP WITH TIME ZONE,
//!         CONSTRAINT email_unique UNIQUE(email),
//!         CONSTRAINT username_pk PRIMARY KEY (username));
//!     \endcode
//!     -# <div id="configuration_data"> The "configurations" table is used by the clients to store they client side configurations.The table
//!         stores the following informations:
//!         -# <b>key:</b> The text represented key that the user uses to access the particular option
//!         -# <b>value:</b> The current configuration value
//!         -# <b>user:</b> The username that the configuration records belongs to
//!         .
//!     Creating the table has been done by the statement:
//!     \code
//!     CREATE TABLE configurations(
//!         key TEXT,
//!         value BYTEA NOT NULL,
//!         user VARCHAR(256) NOT NULL,
//!         CONSTRAINT user_fk FOREIGN KEY (user) REFERENCES users (username),
//!         CONSTRAINT key_pk PRIMARY KEY (key));
//!     \endcode
//!     </div>
//!     -# If a user wants to send binary information, its persisted into the "attachments" table. As configurations, attachments are also assigned
//!         to the user. Take an example: Alice sends Bob an image, the image is inserted by Bob's username into the table. The table stores the
//!         following informations:
//!         -# <b>key:</b> Automincremented key for the next attachment in the table
//!         -# <b>name:</b> The original file name
//!         -# <b>attachment:</b> The file itself
//!         -# <b>user:</b> The user that the atteachment belongs to.
//!         .
//!     Creating the table has been done by the statement:
//!     \code
//!     CREATE TABLE attachments(
//!         key SERIAL,
//!         name VARCHAR(256) NOT NULL,
//!         attachment BYTEA NOT NULL,
//!         user VARCHAR(256) NOT NULL,
//!         CONSTRAINT user_fk FOREIGN KEY (user) REFERENCES users (username),
//!         CONSTRAINT key_pk PRIMARY KEY (key));
//!     \endcode
//!     -# Assuming that the continuous usage of Chat produces lots of data, the conversations are splitted up into several tables. The naming
//!         convention of the table is CDDMMYYHHMMSS where:
//!         -# <b>C:</b> Starting letter of "Conversation"
//!         -# <b>DDMMYY:</b> Current date in UK format
//!         -# <b>HHMMSS:</b> Current time
//!         .
//!     The date and time information show when the table were created. Each of the conversation tables contain configurable number of rows.
//!     The default value is 1000000 rows and it can be overwritten via configuration file between 1 and 2^31 - 1. If the table reaches this row count,
//!     a new table will be created by the web-service. The table stores the following informations:
//!         -# <b>key:</b> Automincremented key for the conversation
//!         -# <b>time:</b> The date and time-stamp where the web-service receives the new conversation. The time-stamp holds the timezone
//!             information as well, that could be differ from the timezone of the message sender. In that case it's up to the client to recalculate
//!             the correct timezone.
//!         -# <b>message:</b> The next message in a conversation
//!         -# <b>user:</b> The author of the message
//!         .
//!     Creating the table has been done by the statement:
//!     \code
//!     CREATE TABLE <CDDMMYYHHMMSS> (
//!         key SERIAL,
//!         time TIMESTAMP WITH TIME ZONE NOT NULL,
//!         message TEXT NOT NULL,
//!         user VARCHAR(256),
//!         CONSTRAINT user_fk FOREIGN KEY (user) REFERENCES users (username),
//!         CONSTRAINT key_pk PRIMARY KEY (key));
//!     \endcode
//!
// =============================================================================
//! \file
//! \copyright
// ======================= end of file: userstory.hpp ==========================
