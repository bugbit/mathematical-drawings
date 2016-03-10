##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=dibuixosAllegro
ConfigurationName      :=Debug
WorkspacePath          := "/datos/proyectos/oscar/dibuixos/v2015/SRC"
ProjectPath            := "/datos/proyectos/oscar/dibuixos/v2015/SRC"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=oscar
Date                   :=20/01/16
CodeLitePath           :="/home/oscar/.codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="dibuixosAllegro.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)alleg 
IncludePCH             :=  -include /datos/proyectos/oscar/dibuixos/v2015/SRC/alleg/pch.h 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)alleg 
ArLibs                 :=  "alleg" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/alleg_main.c$(ObjectSuffix) $(IntermediateDirectory)/dibuixos.c$(ObjectSuffix) $(IntermediateDirectory)/util.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:

# PreCompiled Header
/datos/proyectos/oscar/dibuixos/v2015/SRC/alleg/pch.h.gch: /datos/proyectos/oscar/dibuixos/v2015/SRC/alleg/pch.h
	$(CXX) $(SourceSwitch) /datos/proyectos/oscar/dibuixos/v2015/SRC/alleg/pch.h $(PCHCompileFlags)



##
## Objects
##
$(IntermediateDirectory)/alleg_main.c$(ObjectSuffix): alleg/main.c $(IntermediateDirectory)/alleg_main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/datos/proyectos/oscar/dibuixos/v2015/SRC/alleg/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/alleg_main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/alleg_main.c$(DependSuffix): alleg/main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/alleg_main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/alleg_main.c$(DependSuffix) -MM "alleg/main.c"

$(IntermediateDirectory)/alleg_main.c$(PreprocessSuffix): alleg/main.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/alleg_main.c$(PreprocessSuffix) "alleg/main.c"

$(IntermediateDirectory)/dibuixos.c$(ObjectSuffix): dibuixos.c $(IntermediateDirectory)/dibuixos.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/datos/proyectos/oscar/dibuixos/v2015/SRC/dibuixos.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/dibuixos.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dibuixos.c$(DependSuffix): dibuixos.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dibuixos.c$(ObjectSuffix) -MF$(IntermediateDirectory)/dibuixos.c$(DependSuffix) -MM "dibuixos.c"

$(IntermediateDirectory)/dibuixos.c$(PreprocessSuffix): dibuixos.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dibuixos.c$(PreprocessSuffix) "dibuixos.c"

$(IntermediateDirectory)/util.c$(ObjectSuffix): util.c $(IntermediateDirectory)/util.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/datos/proyectos/oscar/dibuixos/v2015/SRC/util.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/util.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/util.c$(DependSuffix): util.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/util.c$(ObjectSuffix) -MF$(IntermediateDirectory)/util.c$(DependSuffix) -MM "util.c"

$(IntermediateDirectory)/util.c$(PreprocessSuffix): util.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/util.c$(PreprocessSuffix) "util.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/
	$(RM) /datos/proyectos/oscar/dibuixos/v2015/SRC/alleg/pch.h.gch


