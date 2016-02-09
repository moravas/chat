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
//! -# <b>FT001:</b> I, as an unauthenticated user want to see a username and password input fields, a link to
//! register and another to require a forgot password and a login button on which I can perform the following actions:
//!     * Typing my already registered username and password I can log in.
//!     * Clicking on the "Forgot password?" link I can provide my already registered e-mail address and
//!         a message will be sent with a new password.
//!     * Clicking on the "Register" link, I can register by a valid e-mail address, username and password
//!     .
//! <b>Acceptance criteria:</b> The links to register as new user and require new password take place in
//! horizontal order within the vertical order of "username", "password" input fields, links and "Login" button.
//! All of them are in the center of the screen in a resolution independent manner. The actions are valid if
//!     * The user can log in by its username and password
//!     * The user receives an e-mail with a random generated OTP that the user must change just after login
//!     * The user can register with username, e-mail and password. After the registration the user can log in
//!     .
//! -# <b>FT002:</b> I, as an authenticated user want to getting into the default screen after login where I see:
//!     * my conversations in chronological order
//!     * all other registered users in alphabetical order
//!     * a large blank area
//!     .
//! and I can click on one of my last activity and read it or clicking on another user and send message to it.<br>
//! <b>Acceptance criteria:</b>
//!     * After log in the conversations and the registered users appear in a tab card on the left side. The tabs
//!         holds the informations separately. The rest of the screen is inactive
//!     * When the user clicks on one of its conversations, it will be opened on the blank area without possibility to
//!         edit it: the text input field stay hidden
//!     * When the user clicks on the name of a registered user, the text browser will be open on the blank page and
//!         below it a text input field and a "Send" button
//!     .
//!
//! \section userstory User stories
// =============================================================================
//! \file
//! \copyright
// ====================== end of file: requirements.hpp ========================
