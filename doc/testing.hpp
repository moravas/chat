// =============================================================================
//! \file
//! \brief          Requirements
//! \author         Norbert Toth
//! \date           26.02.2016.
//! \note
// =============================================================================
//!
//! \page integration Integration test
//! \tableofcontents
//!
//! \section introduction Introduction
//! The aim of integration tests is to verify the software that it provides the desired behavior against to the particular user story.
//!
//! \section test_items Test items
//! Every feature delivered to the user should be covered by integration test. For the detailed list of affected features see \ref tested_features
//!
//! \section tested_features Tested features
//! \subsection TST001 TST001: Create user account
//! <b>Covered user story:</b> US004: Create user account
//!
//! The purpose of this test is to verify that the server allow creating new user account with proper credentials, but reject malformed requests or
//! requests that try to re-create already existing accounts. The test executes the following steps:
//! -# Registers user with invalid username
//! -# Registers user with incorrect password
//! -# Registers user with malformed email address
//! -# Registers user with valid credentials
//! -# Retry to registers user with same credentials as before
//!
//! <b>Setup:</b><br>
//! Start the web-service on Linux platform and sends the client registration HTTP requests to it. Be careful: the order of requests in the table below
//! is important to guaranty the right result of test.
//!
//! <table>
//!     <tr> <th>API Request</th>
//!         <th>Response</th></tr>
//!     <tr><td>
//!         \code
//!         POST http://localhost/users/register
//!         Content-Type: application/json
//!         {
//!         "username": "Bob",
//!         "password": "ValidBob123",
//!         "email": "bob@domain.com"
//!         }
//!         \endcode
//!         </td>
//!         <td>
//!             400 Bad Request: username is too sort
//!         </td></tr>
//!     <tr><td>
//!         \code
//!         POST http://localhost/users/register
//!         Content-Type: application/json
//!         {
//!         "username": "ValidBob",
//!         "password": "Bob123",
//!         "email": "bob@domain.com"
//!         }
//!         \endcode
//!         </td>
//!         <td>
//!             400 Bad Request: Incorrect password
//!         </td></tr>
//!     <tr><td>
//!         \code
//!         POST http://localhost/users/register
//!         Content-Type: application/json
//!         {
//!         "username": "ValidBob",
//!         "password": "ValidBob123",
//!         "email": "bobdomain.com"
//!         }
//!         \endcode
//!         </td>
//!         <td>
//!             400 Bad Request: Malformed email address
//!         </td></tr>
//!     <tr><td>
//!         \code
//!         POST http://localhost/users/register
//!         Content-Type: application/json
//!         {
//!         "username": "ValidBob",
//!         "password": "ValidBob123",
//!         "email": "bob@domain.com"
//!         }
//!         \endcode
//!         </td>
//!         <td>
//!             201 Created
//!         </td></tr>
//!     <tr><td>
//!         \code
//!         POST http://localhost/users/register
//!         Content-Type: application/json
//!         {
//!         "username": "ValidBob",
//!         "password": "ValidBob123",
//!         "email": "bob@domain.com"
//!         }
//!         \endcode
//!         </td>
//!         <td>
//!             409 Conflict
//!         </td></tr>
//! </table>
//!
//! \subsection TST002 TST002: Loggin in
//! <b>Covered user story:</b> US004: Create user account
//!
//! <b>Setup:</b><br>
//!
//! \subsection TST003 TST003: Delete credentials
//! <b>Covered user story:</b> US004: Create user account
//!
//! <b>Setup:</b><br>
//! Start the web-service on Linux platform and registrer a new user on the server by ValidBob#ValidBob123#bob@domain.com then log in with the
//! new credentials. If everithing went well, perform the following requests on the server:
//! -# Delete the account on the server
//! -# Try to log on onto the server
//! .
//!
//! <table>
//!     <tr> <th>API Request</th>
//!         <th>Response</th></tr>
//!     <tr><td>
//!         \code
//!         DELETE http://localhost/users/ValidBob
//!         X-Authentication-Token:
//!         \endcode
//!         </td>
//!         <td>
//!         200 OK
//!         </td></tr>
//!     <tr><td>
//!         \code
//!         POST http://localhost/users/login
//!         Content-Type: application/json
//!         {
//!         "username": "ValidBob",
//!         "password": "ValidBob123",
//!         }
//!         \endcode
//!         </td>
//!         <td>
//!         401 Unauthorized
//!         </td></tr>
//! </table>
//!
//!
//! \subsection TST004 TST004: Handle configuration data
//! <b>Covered user story:</b> US003: User configuration data management
//!
//! The purpose of this test is to verify the server capability to handle requests correctly which target configuration data insertion regarding a
//! specified user credentials. The test executes the following steps:
//! -# Acquire a resource
//! -# Perform login
//! -# Acquire the same resource as before
//! -# Request the server to store resource and check its availability
//! -# Update the resource that is already inserted and check its availability
//! -# Delete the resource and check the existence of it.
//! .
//!
//! <b>Setup:</b><br>
//! Start the web-service on Linux platform and sends the client registration HTTP requests to it. Be careful: the order of requests in the table below
//! is important to guaranty the right result of test.
//!
//! <table>
//!     <tr> <th>API Request</th>
//!         <th>Response</th></tr>
//!     <tr><td>
//!         \code
//!         GET http://localhost/configuration/ValidBob/background
//!         \endcode
//!         </td>
//!         <td>
//!         401 Unauthorized
//!         </td></tr>
//!     <tr><td>
//!         \code
//!         POST http://localhost/users/login
//!         Content-Type: application/json
//!         {
//!         "username": "ValidBob",
//!         "password": "ValidBob123"
//!         }
//!         \endcode
//!         </td>
//!         <td>
//!         200 OK and the authentication token
//!         </td></tr>
//!     <tr><td>
//!         \code
//!         GET http://localhost/configuration/ValidBob/background
//!         X-Authentication-Token:
//!         \endcode
//!         </td>
//!         <td>
//!         404 Not Found
//!         </td></tr>
//!     <tr><td>
//!         \code
//!         POST http://localhost/configuration/ValidBob
//!         X-Authentication-Token:
//!         Content-Type: application/json
//!         {"background": "0xFFFFFF"}
//!         \endcode
//!         </td>
//!         <td>
//!         201 Created
//!         </td></tr>
//!     <tr><td>
//!         \code
//!         GET http://localhost/configuration/ValidBob/background
//!         X-Authentication-Token:
//!         \endcode
//!         </td>
//!         <td>
//!         200 OK and the resource: {"background": "0xFFFFFF"}
//!         </td></tr>
//!     <tr><td>
//!         \code
//!         POST http://localhost/configuration/ValidBob
//!         X-Authentication-Token:
//!         Content-Type: application/json
//!         {"background": "0xFFFFF0"}
//!         \endcode
//!         </td>
//!         <td>
//!         200 OK
//!         </td></tr>
//!     <tr><td>
//!         \code
//!         GET http://localhost/configuration/ValidBob/background
//!         X-Authentication-Token:
//!         \endcode
//!         </td>
//!         <td>
//!         200 OK and the resource: {"background": "0xFFFFF0"}
//!         </td></tr>
//!     <tr><td>
//!         \code
//!         DELETE http://localhost/configuration/ValidBob/background
//!         X-Authentication-Token:
//!         \endcode
//!         </td>
//!         <td>
//!         200 OK
//!         </td></tr>
//! </table>
//!
// =============================================================================
//! \file
//! \copyright
// ======================== end of file: testing.hpp ===========================
