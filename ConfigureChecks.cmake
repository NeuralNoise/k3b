include(CheckIncludeFile)
include(CheckSymbolExists)
include(CheckFunctionExists)
include(CheckLibraryExists)
include(CheckPrototypeExists)
include(CheckTypeSize)
include(CheckStructMember)
include(CheckCXXSourceCompiles)

macro_bool_to_01(ADD_K3B_DEBUG K3B_DEBUG)
macro_bool_to_01(MUSICBRAINZ_FOUND HAVE_MUSICBRAINZ)

