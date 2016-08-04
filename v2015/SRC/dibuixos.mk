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
Date                   :=04/08/16
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
ObjectsFileList        :="dibuixos.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
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
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/dibuixos.c$(ObjectSuffix) $(IntermediateDirectory)/presentacio.c$(ObjectSuffix) $(IntermediateDirectory)/timer.c$(ObjectSuffix) $(IntermediateDirectory)/glutil.c$(ObjectSuffix) 



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

$(IntermediateDirectory)/presentacio.c$(ObjectSuffix): presentacio.c $(IntermediateDirectory)/presentacio.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/oscar/Proyectos/oscar/dibuixos/v2015/SRC/presentacio.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/presentacio.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/presentacio.c$(DependSuffix): presentacio.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/presentacio.c$(ObjectSuffix) -MF$(IntermediateDirectory)/presentacio.c$(DependSuffix) -MM "presentacio.c"

$(IntermediateDirectory)/presentacio.c$(PreprocessSuffix): presentacio.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/presentacio.c$(PreprocessSuffix) "presentacio.c"

$(IntermediateDirectory)/timer.c$(ObjectSuffix): timer.c $(IntermediateDirectory)/timer.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/oscar/Proyectos/oscar/dibuixos/v2015/SRC/timer.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/timer.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/timer.c$(DependSuffix): timer.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/timer.c$(ObjectSuffix) -MF$(IntermediateDirectory)/timer.c$(DependSuffix) -MM "timer.c"

$(IntermediateDirectory)/timer.c$(PreprocessSuffix): timer.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/timer.c$(PreprocessSuffix) "timer.c"

$(IntermediateDirectory)/glutil.c$(ObjectSuffix): glutil.c $(IntermediateDirectory)/glutil.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/oscar/Proyectos/oscar/dibuixos/v2015/SRC/glutil.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/glutil.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/glutil.c$(DependSuffix): glutil.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/glutil.c$(ObjectSuffix) -MF$(IntermediateDirectory)/glutil.c$(DependSuffix) -MM "glutil.c"

$(IntermediateDirectory)/glutil.c$(PreprocessSuffix): glutil.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/glutil.c$(PreprocessSuffix) "glutil.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/
	$(RM) /home/oscar/Proyectos/oscar/dibuixos/v2015/SRC/pch.h.gch


