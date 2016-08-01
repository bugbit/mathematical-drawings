##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=dibuixos
ConfigurationName      :=Debug
WorkspacePath          := "/home/oscar/Proyectos"
ProjectPath            := "/home/oscar/Proyectos/oscar/dibuixos/v2015/SRC"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=oscar
Date                   :=02/08/16
CodeLitePath           :="/home/oscar/.codelite"
LinkerName             :=gcc
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
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
ObjectsFileList        :="dibuixos.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  $(shell sdl2-config --libs)
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)GL $(LibrarySwitch)GLU $(LibrarySwitch)glut 
ArLibs                 :=  "GL" "GLU" "glut" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := gcc
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(shell sdl2-config --cflags) $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/dibuixos.c$(ObjectSuffix) $(IntermediateDirectory)/src_Presentacion.c$(ObjectSuffix) 



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

PostBuild:
	@echo Executing Post Build commands ...
	cp -R ./data ./Debug/data
	@echo Done

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:

# PreCompiled Header
/home/oscar/Proyectos/oscar/dibuixos/v2015/SRC/pch.h.gch: /home/oscar/Proyectos/oscar/dibuixos/v2015/SRC/pch.h
	$(CXX) $(SourceSwitch) /home/oscar/Proyectos/oscar/dibuixos/v2015/SRC/pch.h $(PCHCompileFlags)



##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/oscar/Proyectos/oscar/dibuixos/v2015/SRC/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM "main.c"

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) "main.c"

$(IntermediateDirectory)/dibuixos.c$(ObjectSuffix): dibuixos.c $(IntermediateDirectory)/dibuixos.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/oscar/Proyectos/oscar/dibuixos/v2015/SRC/dibuixos.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/dibuixos.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dibuixos.c$(DependSuffix): dibuixos.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dibuixos.c$(ObjectSuffix) -MF$(IntermediateDirectory)/dibuixos.c$(DependSuffix) -MM "dibuixos.c"

$(IntermediateDirectory)/dibuixos.c$(PreprocessSuffix): dibuixos.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dibuixos.c$(PreprocessSuffix) "dibuixos.c"

$(IntermediateDirectory)/src_Presentacion.c$(ObjectSuffix): src/Presentacion.c $(IntermediateDirectory)/src_Presentacion.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/oscar/Proyectos/oscar/dibuixos/v2015/SRC/src/Presentacion.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_Presentacion.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_Presentacion.c$(DependSuffix): src/Presentacion.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_Presentacion.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_Presentacion.c$(DependSuffix) -MM "src/Presentacion.c"

$(IntermediateDirectory)/src_Presentacion.c$(PreprocessSuffix): src/Presentacion.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_Presentacion.c$(PreprocessSuffix) "src/Presentacion.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/
	$(RM) /home/oscar/Proyectos/oscar/dibuixos/v2015/SRC/pch.h.gch


