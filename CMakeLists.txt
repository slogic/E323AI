### Generic native Skirmish AI config
#
set(mySourceDirRel         "") # Common values are "" or "src"
set(additionalSources      ${CUtils_SRC})
set(additionalCompileFlags "")
set(additionalLibraries    ${LegacyCpp_AIWRAPPER_TARGET} ${SDL_LIBRARY})

ConfigureNativeSkirmishAI(mySourceDirRel additionalSources additionalCompileFlags additionalLibraries)
