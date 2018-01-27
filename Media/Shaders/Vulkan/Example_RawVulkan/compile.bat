@echo off 
setlocal enabledelayedexpansion

cd %CD%

rem for %%i in (*.vert) do glslangValidator.exe %%i -S "vert" -V -o %%i.spv
rem for %%i in (*.frag) do glslangValidator.exe %%i -S "frag" -V -o %%i.spv


for %%a in (*.glsl.vertex-shader) do ( 
	set oldName=%%a 
	set newName=!oldName:glsl=spir-v! 
	glslangValidator.exe !oldName! -S "vert" -V -o !newName!
) 

for %%a in (*.glsl.tessellation-control-shader) do ( 
	set oldName=%%a 
	set newName=!oldName:glsl=spir-v! 
	glslangValidator.exe !oldName! -S "tesc" -V -o !newName!
) 

for %%a in (*.glsl.tessellation-evaluation-shader) do ( 
	set oldName=%%a 
	set newName=!oldName:glsl=spir-v! 
	glslangValidator.exe !oldName! -S "tese" -V -o !newName!
) 

for %%a in (*.glsl.geometry-shader) do ( 
	set oldName=%%a 
	set newName=!oldName:glsl=spir-v! 
	glslangValidator.exe !oldName! -S "geom" -V -o !newName!
) 

for %%a in (*.glsl.fragment-shader) do ( 
	set oldName=%%a 
	set newName=!oldName:glsl=spir-v! 
	glslangValidator.exe !oldName! -S "frag" -V -o !newName!
) 


pause