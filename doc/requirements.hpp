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
//! -# <b>FT001:</b> I, as a webservice client want to communicate in a fullduplex manner to the server via a secure chanel.<br>
//! <b>Acceptance criteria:</b> The applied communication protocol is secure web socket(wss) or HTTPS that use TLS.
//!
//! -# <b>FT002:</b> I, as an unathenticated webservice client want to sign in into the server via my username and password.<br>
//! <b>Acceptance criteria:</b> The client sends its username and password. If they indentify a registered user and valid, the
//! server alow the client to log in.
//!
//! -# <b>FT003:</b> I, as an unathenticated webservice client want to register on the server.<br>
//! <b>Acceptance criteria:</b> The client sends username, password and email address to the server via HTTPS POST.
//! The registration is success if the username and password isn't already used on the server.
//!
//! -# <b>FT004:</b> I, as an authenticated webservice client want to get the list of registered users.<br>
//! <b>Acceptance criteria:</b> The client sends an HTTPS GET and the response contains the username of registered users. The
//! reply is empty only if there is no users registered on the server.
//!
//! -# <b>FT005:</b> I, as an authenticated webservice client want to get notification about the state change of the cleints.<br>
//! <b>Acceptance criteria:</b> The client receives notification if the state of another users changed. The granularity of
//! notifications is one user.
//!
//! -# <b>FT006:</b> I, as an authenticated webservice client want to send text messages to my conversation partner.<br>
//! <b>Acceptance criteria:</b> The client sends HTTPS POST to the server that persists the message. If everithing was successfull,
//! the conversation partner receives a notification.
//!
//! \section userstory User stories
// =============================================================================
//! \file
//! \copyright
// ====================== end of file: requirements.hpp ========================
