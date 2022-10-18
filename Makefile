Graphics = -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main  C:\mingw_dev_lib\bin\SDL2.dll
Include = Software/TSauce/include
Math = -I $(Include)/Math $(Include)/Math/vectormath.cpp
Driver = -I $(Include)/Drivers $(Include)/Drivers/GLDriver.cpp
R2D = -I $(Include)/Renderer $(Include)/Renderer/R2D.cpp
Objects = $(Include)/Renderer/R3D.cpp $(Include)/Renderer/Poly.cpp  $(Include)/Renderer/Object.cpp 

IBP:
	g++ -g $(Graphics) $(Math) $(Driver) $(R2D) $(Objects) Out/ibp.cpp -o Out/ibp.exe
	clear