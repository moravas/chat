// =============================================================================
//! \file
//! \brief
//! \author         Norbert Toth
//! \date           08.02.2016.
//! \note
// =============================================================================

//! \page guideline Coding guideline
//! \tableofcontents
//! This page introduces the file formats and naming conventions. In case of undeclared points,
//! the commonly used formats have to be used. This rules don't concern for the third party sources
//!
//! \section fileformat File outline
//! In the following, we will determine the main characteristics of the source files. First of all,
//! every new source file have to contain a standard header and footer listed below.
//! * The header has to contains at least the following listed fields filled out with the proper
//! datas.
//! * On demand, the developer can past more exlpanation about the file.
//!
//! // =============================================================================<br>
//! //! \\file<br>
//! //! \\brief<br>
//! //! \\author<br>
//! //! \\date<br>
//! //! \\note<br>
//! // =============================================================================<br>
//!
//! \note Keep in mind, that this sections aren't for documenting the source. Informations in these
//! fields belong to the file itself!
//!
//! * The footer contains a "copyright" field. Fill out is optional.
//! * The last not empty line of the file contains the proper name of the file with its suffix.
//!
//! // =============================================================================<br>
//! //! \\file<br>
//! //! \\copyright<br>
//! // ================== end of file:  =======================<br>
//!
//! Furthermore, it would be welcomed to be separated each logical sections, like:
//! * includes for one specific third party library, e.g.: OS, IP stack, etc
//! * type or prototype declarations, e.g.: class, enum, global function or variable declarations
//! * inline function definition
//! * ctor / dtor definitions are separeted from the other sections
//!
//! The suggested separator format is:<br>
//! // =============================================================================<br>
//! // short section description<br>
//! // =============================================================================<br>
//!
//! Relating to the classes separations should be applied. Within the separators the
//! applied order by visibility is the:
//! * public
//! * protected
//! * private
//!	.
//! The applied separators listed below:
//! * The class should has the following header:<br>
//! // =============================================================================<br>
//! //! \\brief<br>
//! //!<br>
//! //! <detailed description here\><br>
//! // =============================================================================<br>
//! * At the top of the class the section separator takes place for Ctors / Dtors<br>
//! // =============================================================================<br>
//! // Section for Ctor / Dtor<br>
//! // =============================================================================<br>
//! * The section above is followed by the implemented or overridden methods<br>
//! // =============================================================================<br>
//! // Section for Implement / Overridden<br>
//! // =============================================================================<br>
//! * Any other methods<br>
//! // =============================================================================<br>
//! // Section for Other methods<br>
//! // =============================================================================<br>
//! * Member declarations<br>
//! // =============================================================================<br>
//! // Section for Member declaration<br>
//! // =============================================================================<br>
//!
//! \section codingstyle Coding styles
//! In the section, we will list the required naming conventions. If a rule isn't listed here, please
//! use one of the commonly applied formats.
//!
//! * For member or global <b>function</b> declaration use the camelStyle
//! * <b>Macros</b> has to be written with CAPITAL letter
//! * <b>Macros</b> has to be SEPARETED_WITH_UNDERSCORES
//! * <b>Private class member</b> has to start with "_"
//!
//! \note The third party sources are exceptions from this guideline!
// =============================================================================
//! \file
//! \copyright
// =================== end of file: codingguideline.hpp ========================
