##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=dibuixos
ConfigurationName      :=Debug
WorkspacePath          := "/datos/proyectos/oscar/dibuixos/v2017"
ProjectPath            := "/datos/proyectos/oscar/dibuixos/v2017"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=oscar
Date                   :=28/12/16
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
LinkOptions            :=  `sdl2-config --libs`
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)GL $(LibrarySwitch)GLU $(LibrarySwitch)SDL2_mixer 
ArLibs                 :=  "GL" "GLU" "SDL2_mixer" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O3 -O0 -Wall `sdl2-config --cflags` $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/dibuixos.c$(ObjectSuffix) $(IntermediateDirectory)/demo.c$(ObjectSuffix) $(IntermediateDirectory)/util.c$(ObjectSuffix) $(IntermediateDirectory)/glutil.c$(ObjectSuffix) $(IntermediateDirectory)/fg_font.c$(ObjectSuffix) $(IntermediateDirectory)/fg_font_data.c$(ObjectSuffix) $(IntermediateDirectory)/fg_stroke_mono_roman.c$(ObjectSuffix) $(IntermediateDirectory)/fg_stroke_roman.c$(ObjectSuffix) $(IntermediateDirectory)/timer.c$(ObjectSuffix) \
	$(IntermediateDirectory)/ninedigitsofpi.c$(ObjectSuffix) $(IntermediateDirectory)/pi.c$(ObjectSuffix) 



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
	rm -f -R ./Debug/data
	cp -R ./data ./Debug/data
	@echo Done

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:

# PreCompiled Header
pch.h.gch: pch.h
	$(CXX) $(SourceSwitch) pch.h $(PCHCompileFlags)



##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/datos/proyectos/oscar/dibuixos/v2017/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM "main.c"

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) "main.c"

$(IntermediateDirectory)/dibuixos.c$(ObjectSuffix): dibuixos.c $(IntermediateDirectory)/dibuixos.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/datos/proyectos/oscar/dibuixos/v2017/dibuixos.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/dibuixos.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dibuixos.c$(DependSuffix): dibuixos.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dibuixos.c$(ObjectSuffix) -MF$(IntermediateDirectory)/dibuixos.c$(DependSuffix) -MM "dibuixos.c"

$(IntermediateDirectory)/dibuixos.c$(PreprocessSuffix): dibuixos.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dibuixos.c$(PreprocessSuffix) "dibuixos.c"

$(IntermediateDirectory)/demo.c$(ObjectSuffix): demo.c $(IntermediateDirectory)/demo.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/datos/proyectos/oscar/dibuixos/v2017/demo.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/demo.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/demo.c$(DependSuffix): demo.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/demo.c$(ObjectSuffix) -MF$(IntermediateDirectory)/demo.c$(DependSuffix) -MM "demo.c"

$(IntermediateDirectory)/demo.c$(PreprocessSuffix): demo.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/demo.c$(PreprocessSuffix) "demo.c"

$(IntermediateDirectory)/util.c$(ObjectSuffix): util.c $(IntermediateDirectory)/util.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/datos/proyectos/oscar/dibuixos/v2017/util.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/util.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/util.c$(DependSuffix): util.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/util.c$(ObjectSuffix) -MF$(IntermediateDirectory)/util.c$(DependSuffix) -MM "util.c"

$(IntermediateDirectory)/util.c$(PreprocessSuffix): util.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/util.c$(PreprocessSuffix) "util.c"

$(IntermediateDirectory)/glutil.c$(ObjectSuffix): glutil.c $(IntermediateDirectory)/glutil.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/datos/proyectos/oscar/dibuixos/v2017/glutil.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/glutil.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/glutil.c$(DependSuffix): glutil.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/glutil.c$(ObjectSuffix) -MF$(IntermediateDirectory)/glutil.c$(DependSuffix) -MM "glutil.c"

$(IntermediateDirectory)/glutil.c$(PreprocessSuffix): glutil.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/glutil.c$(PreprocessSuffix) "glutil.c"

$(IntermediateDirectory)/fg_font.c$(ObjectSuffix): fg_font.c $(IntermediateDirectory)/fg_font.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/datos/proyectos/oscar/dibuixos/v2017/fg_font.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/fg_font.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/fg_font.c$(DependSuffix): fg_font.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/fg_font.c$(ObjectSuffix) -MF$(IntermediateDirectory)/fg_font.c$(DependSuffix) -MM "fg_font.c"

$(IntermediateDirectory)/fg_font.c$(PreprocessSuffix): fg_font.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/fg_font.c$(PreprocessSuffix) "fg_font.c"

$(IntermediateDirectory)/fg_font_data.c$(ObjectSuffix): fg_font_data.c $(IntermediateDirectory)/fg_font_data.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/datos/proyectos/oscar/dibuixos/v2017/fg_font_data.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/fg_font_data.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/fg_font_data.c$(DependSuffix): fg_font_data.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/fg_font_data.c$(ObjectSuffix) -MF$(IntermediateDirectory)/fg_font_data.c$(DependSuffix) -MM "fg_font_data.c"

$(IntermediateDirectory)/fg_font_data.c$(PreprocessSuffix): fg_font_data.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/fg_font_data.c$(PreprocessSuffix) "fg_font_data.c"

$(IntermediateDirectory)/fg_stroke_mono_roman.c$(ObjectSuffix): fg_stroke_mono_roman.c $(IntermediateDirectory)/fg_stroke_mono_roman.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/datos/proyectos/oscar/dibuixos/v2017/fg_stroke_mono_roman.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/fg_stroke_mono_roman.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/fg_stroke_mono_roman.c$(DependSuffix): fg_stroke_mono_roman.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/fg_stroke_mono_roman.c$(ObjectSuffix) -MF$(IntermediateDirectory)/fg_stroke_mono_roman.c$(DependSuffix) -MM "fg_stroke_mono_roman.c"

$(IntermediateDirectory)/fg_stroke_mono_roman.c$(PreprocessSuffix): fg_stroke_mono_roman.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/fg_stroke_mono_roman.c$(PreprocessSuffix) "fg_stroke_mono_roman.c"

$(IntermediateDirectory)/fg_stroke_roman.c$(ObjectSuffix): fg_stroke_roman.c $(IntermediateDirectory)/fg_stroke_roman.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/datos/proyectos/oscar/dibuixos/v2017/fg_stroke_roman.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/fg_stroke_roman.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/fg_stroke_roman.c$(DependSuffix): fg_stroke_roman.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/fg_stroke_roman.c$(ObjectSuffix) -MF$(IntermediateDirectory)/fg_stroke_roman.c$(DependSuffix) -MM "fg_stroke_roman.c"

$(IntermediateDirectory)/fg_stroke_roman.c$(PreprocessSuffix): fg_stroke_roman.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/fg_stroke_roman.c$(PreprocessSuffix) "fg_stroke_roman.c"

$(IntermediateDirectory)/timer.c$(ObjectSuffix): timer.c $(IntermediateDirectory)/timer.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/datos/proyectos/oscar/dibuixos/v2017/timer.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/timer.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/timer.c$(DependSuffix): timer.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/timer.c$(ObjectSuffix) -MF$(IntermediateDirectory)/timer.c$(DependSuffix) -MM "timer.c"

$(IntermediateDirectory)/timer.c$(PreprocessSuffix): timer.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/timer.c$(PreprocessSuffix) "timer.c"

$(IntermediateDirectory)/ninedigitsofpi.c$(ObjectSuffix): ninedigitsofpi.c $(IntermediateDirectory)/ninedigitsofpi.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/datos/proyectos/oscar/dibuixos/v2017/ninedigitsofpi.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ninedigitsofpi.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ninedigitsofpi.c$(DependSuffix): ninedigitsofpi.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ninedigitsofpi.c$(ObjectSuffix) -MF$(IntermediateDirectory)/ninedigitsofpi.c$(DependSuffix) -MM "ninedigitsofpi.c"

$(IntermediateDirectory)/ninedigitsofpi.c$(PreprocessSuffix): ninedigitsofpi.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ninedigitsofpi.c$(PreprocessSuffix) "ninedigitsofpi.c"

$(IntermediateDirectory)/pi.c$(ObjectSuffix): pi.c $(IntermediateDirectory)/pi.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/datos/proyectos/oscar/dibuixos/v2017/pi.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/pi.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pi.c$(DependSuffix): pi.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/pi.c$(ObjectSuffix) -MF$(IntermediateDirectory)/pi.c$(DependSuffix) -MM "pi.c"

$(IntermediateDirectory)/pi.c$(PreprocessSuffix): pi.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pi.c$(PreprocessSuffix) "pi.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/
	$(RM) pch.h.gch


