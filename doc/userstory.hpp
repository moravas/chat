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
//! \subsection US001 US001: User password security
//! <b>Affected features:</b> <a href="#FT002">FT002</a><br>
//! If a user registers to use a service that expect authentication, he expects him credentials to be in safe. So user passwords are stored in 
//! encrypted form. To encrypt it, the SHA256 hash is generated from the master key and used AES based encryption.
//!
//! The master key is an in-memory password that the system reads in at start from a file. The file path specified as command line argument as 
//! <em> -keyfile \< path_to_file \> </em> that allow administrators to store the file in separated devices and remove it after system start.
//!
//! The MasterKeyManager uses singleton pattern to exist in the system and provide the full functionality to encrypt passwords going trough the
//! REST API controllers.
//!
//! \subsection US002 US002: Request authentication
//! <b>Affected features:</b>
//! <a href="#FT002">FT002</a>,
//! <a href="#FT004">FT004</a>,
//! <a href="#FT005">FT005</a>,
//! <a href="#FT006">FT006</a>,
//! <a href="#FT007">FT007</a>,
//! <a href="#FT008">FT008</a><br>
//! If the server receives a REST API request, it must be authenticated before executing it. The digest based authentication uses HMAC scheme with 
//! SHA512 where the signature hash is the concatenation of the following fields:
//! -# HTTP method
//! -# Request URI
//! -# Username
//! -# Timestamp in UNIX time represented form
//! -# Nonce, which can be a GUID or whatever else that the client choose
//! -# The request payload if it's present in base 64 string represented form
//! .
//! The generated signature concatenated together the username, timestamp nonce and placed into the "Authorization" header. They are separated by ':'
//! character:
//! \code
//! Authorization: <username>:<base_64_represented_signature>:<timestamp>:<nonce>
//! \endcode
//! If a request arrived and authentication is required, the nonce and the timestamp are cached in Redis in-memory cache with 5 minutes expiration 
//! time. By this way the memory occupation is under control. The signature is valid if (the order of the enumeration defines the validation steps):
//! -# The timestamp in the authentication header isn't older as 5 minutes
//! -# There is no similar item in the cache
//! -# The server can regenerate the same hash knowing the nonce, timestamp and username as the request contains
//!
//! \warning The memory overflow control helps to maintain memory consumption in case of normal operation but unable to prevent a DOS attack, when 
//! the system can be flooded by thousands of requests.
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
//!     POST http://<server_URL>/configuration/<username>
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
//!     Getting back a particular configuration has been done by HTTP GET request:
//!     \code
//!     GET http://<server_URL>/configuration/<username>/<key>
//!     \endcode
//!     The operation can result the following error codes:
//!         -# <b>200 OK:</b> Returned by the new resource
//!         -# <b>400 Bad Request:</b> Unknown error occurred
//!         -# <b>401 Unauthorized:</b> The request tried to access resource that is forbidden for it
//!         -# <b>404 Not Found:</b> The request tried to access resource that is not exists on the server
//!         .
//!     Querying multiple resource at once isn't supported yet.
//!
//!     If the client wants to delete item (e.g.: its not needed anymore), then it can be done by sending a DELETE request:
//!     \code
//!     DELETE http://<server_URL>/configuration/<username>/<key_to_be_deleted>
//!     \endcode
//!     The operation result is <b>200 OK</b> in every cases.
//!
//! \subsection US004 US004: User account control
//! <b>Affected features:</b> <a href="#FT003">FT003</a>, <a href="#FT004">FT004</a><br>
//! Regarding a particular user account, the client allowed to create, delete accounts on the server and query the list of registered users if these 
//! requests satisfies their requirements.
//! \subsubsection create_user_account Create user account
//! Creating a new account can be done by the following request:
//! \code
//! POST http://<server_URL>/users/register
//! Content-Type: application/json
//! {
//! "username": "ValidBob",
//! "password": "ValidBob123",
//! "email": "bob@domain.com"
//! }
//! \endcode
//! Where the fields included in the request fulfil the followings:
//! -# The username:
//!     -# Is between 6 and 256 characters
//!     -# Starts with alphanumerical character
//!     -# Can include any special character
//!     .
//! -# The password:
//!     -# Must be at least 8 long
//!     -# Must include at least 2 numerical character, 2 lower-case and 2 upper-case characters
//!     .
//! -# The email address satisfies the well-known email format: someid@domain.domain:
//! .
//! If these requirements are fulfilled, the web-server tries to append a new record into the user table. Due to security reasons, the password is 
//! <a href="#US001">encrypted</a>. The operation results one of the following error codes:
//!     -# <b>201 Created: </b>Everything went fine, the user credential is active and the user now can log in.
//!     -# <b>400 Bad Request: </b>One or more argument of the registration is not fulfil the required form.
//!     -# <b>409 Conflict: </b>There is an user already registered with the same username and password.
//!
//! \subsubsection delete_user_account Delete user account
//! The account can be deleted by the following authenticated request:
//! \code
//! DELETE http://<server_URL>/users/<username>
//! \endcode
//! The operation results one of the following error codes:
//!     -# <b>200 OK: </b>The user credentials are no longer available.
//!     -# <b>401 Unauthorized: </b>Invalid authentication.
//!
//! \subsubsection query_user_list Query users
//! If an authenticated client wants to query the list of registered users, e.g.: displaying it for the human user, it can be done by the following
//! <a href="#US002">authenticated</a> query:
//! \code
//! GET http://<server_URL>/users
//! \endcode
//! The operation results the list of users in JSON represented form:
//! \code
//! HTTP/1.1 200 OK
//! Content-Type: application/json
//! {
//! "users": ["ValidBob", "Alice", "Suzy"]
//! }
//! \endcode
//! The operation results one of the following error codes:
//!     -# <b>200 OK: </b>The client gets back the requested list. Please note, that the request never ever should return empty list because it means that
//!         an unauthorized request went trough the identification
//!     -# <b>401 Unauthorized: </b>Invalid authentication
//!
//! \subsection US005 US005: Database
//! <b>Depends on user stories:</b> </a><br>
//! <b>Affected features:</b> <a href="#FT003">FT003</a>, <a href="#FT008">FT008</a><br>
//! The Chat based on PostgreSQL database and uses of the following tables:
//!     -# The "users" table is the most important one because it stores every necessary informations about the registered users. They are
//!         mandatory to register new users or authenticate an existent one. The table stores the following informations:
//!         -# <b>id:</b> autoincremented integer key
//!         -# <b>username:</b> 256 character max length, stores the username
//!         -# <b>email:</b> 256 character max length, stores the email address of the user
//!         -# <b>pwd:</b> the encrypted password
//!         -# <b>logoff:</b> The last log off time of the user. Using it optional and can affect the client side operations
//!         .
//!     Creating the table has been done by the statement:
//!     \code
//!     CREATE TABLE users(
//!         id SERIAL,
//!         username VARCHAR(256) NOT NULL,
//!         email VARCHAR(256) NOT NULL,
//!         password VARCHAR(128) NOT NULL,
//!         logoff TIMESTAMP WITH TIME ZONE,
//!         CONSTRAINT unique_constraints UNIQUE(username, email, password),
//!         CONSTRAINT users_pk PRIMARY KEY (id));
//!     \endcode
//!     -# <div id="configuration_data"> The "configurations" table is used by the clients to store they client side configurations.The table
//!         stores the following informations:
//!         -# <b>id:</b> autoincremented integer key
//!         -# <b>key:</b> The text represented key that the user uses to access the particular option
//!         -# <b>value:</b> The current configuration value
//!         -# <b>user_id:</b> The username that the configuration records belongs to
//!         .
//!     Creating the table has been done by the statement:
//!     \code
//!     CREATE TABLE configurations(
//!     	id BIGSERIAL,
//!         key TEXT NOT NULL,
//!         value BYTEA NOT NULL,
//!         userid SERIAL NOT NULL,
//!         CONSTRAINT configurations_fk FOREIGN KEY (userid) REFERENCES users (id),
//!         CONSTRAINT configurations_pk PRIMARY KEY (id));
//!     \endcode
//!     </div>
//!     -# If a user wants to send binary information, it is persisted into the "attachments" table. As configurations, attachments are also assigned
//!         to the user. Take an example: Alice sends Bob an image, the image is inserted by Bob's username into the table. The table stores the
//!         following informations:
//!         -# <b>id:</b> Automincremented key for the next attachment in the table
//!         -# <b>name:</b> The original file name
//!         -# <b>value:</b> The file itself in binary stream representation
//!         -# <b>user_id:</b> The user that the attachment belongs to.
//!         .
//!     Creating the table has been done by the statement:
//!     \code
//!     CREATE TABLE attachments(
//!         id SERIAL,
//!         name VARCHAR(256) NOT NULL,
//!         value BYTEA NOT NULL,
//!         userid SERIAL NOT NULL,
//!         CONSTRAINT attachments_fk FOREIGN KEY (userid) REFERENCES users (id),
//!         CONSTRAINT attachments_pk PRIMARY KEY (id));
//!     \endcode
//!     -# The "conversations" table stores the text based messages. It stores the following informations:
//!         -# <b>id:</b> Automincremented key for the conversation
//!         -# <b>time:</b> The date and time-stamp where the web-service receives the new message. The time-stamp holds the timezone information as
//!             well, that could be differ from the timezone of the message sender. In that case it's up to the client to recalculate the correct
//!             timezone.
//!         -# <b>message:</b> The next message in a conversation
//!         -# <b>sender_id:</b> The author of the message
//!         -# <b>receiver_id:</b> The addressee of the message
//!         .
//!     Creating the table has been done by the statement:
//!     \code
//!     CREATE TABLE conversations (
//!         id BIGSERIAL,
//!         time TIMESTAMP WITH TIME ZONE NOT NULL,
//!         message TEXT NOT NULL,
//!         senderid SERIAL,
//!         CONSTRAINT conversations_sender_fk FOREIGN KEY (senderid) REFERENCES users (id),
//!         CONSTRAINT conversations_pk PRIMARY KEY (id));
//!     \endcode
//!     In order to create connection between the message and the user, an additional switch table should be used, that stores:
//!         -# <b>message:</b> The Id of the message
//!         -# <b>user:</b> The user who received the message
//!     Creating the table has been done by the statement:
//!     \code
//!     CREATE TABLE message_user_switch (
//!         messageid BIGSERIAL NOT NULL,
//!         userid SERIAL NOT NULL,
//!         CONSTRAINT message_user_switch_message_fk FOREIGN KEY (messageid) REFERENCES conversations (id),
//!         CONSTRAINT message_user_switch_user_fk FOREIGN KEY (userid) REFERENCES users (id));
//!     \endcode
//!
//! \subsection US006 US006: Conversation manager
//! <b>Affected features:</b> <a href="#FT006">FT006</a><br>
//! Conversation messages are based on JSON represented text messages. They can play both of command and message roles. For example, inviting a new
//! participant can be done by the message:
//! \code
//!     { "invite":[ {"username":"user"} ]}
//! \endcode
//! or:
//! \code
//!     { "id": "124", "invite":[ {"username":"user"} ]}
//! \endcode
//! The examples above are similar. The only difference is that the first one creates a new session but the other one invites the user "user" into
//! the session labelled by session ID "124". Invited users are represented as array even if only one user were invited. Closing a session is very
//! similar:
//! \code
//!     { "id": "124", "close":"user" }
//! \endcode
//! Receiving the close message only accepted form the client who wants to exit from a particular session. Excluding another user is prohibited. The
//! server should be prepared to prevent such a cases because they assume attack against to the server or another clients. If there are no more clients
//! in the current session except the sender one, the Session listener will send back an empty session message:
//! \code
//!     { "id": "124", "property":"empty" }
//! \endcode
//! In this case, it is up to the client to discard the message or re-invite the participants and sends the message again.
//! The messages above are command which targets the server to perform some operations on it, but for messaging client around the word should be
//! forward the incoming message.
//!
//! The text message looks like this:
//! \code
//!     {
//!     "id": "124",
//!     "sender":"user",
//!     "message": "arbitrary text message"
//!     }
//! \endcode
//! It can be seen that the message doesn't holds any information the addresses, but the originator is present.
//!
//! \subsubsection initiate_conversation Initiate conversation
//! After the client logged on to the server, the client is responsible for opening a new socket. This socket will be registered by Conversation
//! manager identified by the username. If the user sends an invitation message to the server, the Conversation manager looks for the session ID in
//! the message and use it or create a new one and checks whether a connection exists identified by the username.
//!     -# If there were no session ID in the invitation message, the Conversation manager deploys new Session Listener and provides to it a list
//!         containing the username and sockets. If it is done, the Conversation manager sends back the session ID to the client.
//!     -# If the session already exists, the session manager appends the list (at least one item) of invited username and socket pairs to the
//!         Session listener.
//!     .
//! \note The socket could be NULL, in this case the client sends off-line messages that could be queried by the conversation partner it will be
//! back again.
//!
//! \subsubsection conversation Conversation
//! If the new message received by the Conversation manager, it looks for a Session listener specified by the session ID and forward the message to it.
//! The Session listener perform the following operations:
//!     -# Persist the message into the "conversations" table
//!     -# Persist insert the message ID and the ID of addressed users into the "message_user_switch" table
//!     -# Walk trough its listeners and forwards the message to them except the sender and off-line clients
//!     .
//! If any error occurred during these operations, the Session listener will hang on its activity and returns to the Conversation manager.
//!
//! \subsubsection close_conversation Close conversation
//! If the client wants to exit from a conversation, sends the "close" command to the server. In this case the socket itself still alive, but the
//! Session listener unregisters the particular client. After exiting from the session, the client doesn't receive messages from clients in that
//! session. Re-invite the client is possible into the session.
//!
//! If the client closes the socket as well, the Conversation manager is responsible for unregister the socket from the Session listeners and persist
//! the log off time-stamp into the "users" table.
//!
// =============================================================================
//! \file
//! \copyright
// ======================= end of file: userstory.hpp ==========================
