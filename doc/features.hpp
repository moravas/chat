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
//! -# <div id="FT008"><b>FT008:</b> I, as an authenticated web service client want to be able to store arbitrary size and count of configuration
//! data on the server concerning to my client side application.<br>
//! <b>Acceptance criteria:</b> The client uses HTTPS POST to create or modify configuration data and DELETE for removing existing one.</div>
//!
// =============================================================================
//! \file
//! \copyright
// ======================== end of file: features.hpp ==========================
