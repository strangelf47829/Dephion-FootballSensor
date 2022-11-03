Strict = -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused
Graphics = -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main  C:\mingw_dev_lib\bin\SDL2.dll
Include = Software/TSauce/include
Include2 = Software/TSauce/Embedded\ Software\include
Math = -I $(Include)/Math $(Include)/Math/vectormath.cpp
Drivers = -I $(Include)/Drivers $(Include)/Drivers/GLDriver.cpp $(Include)/Drivers/FileDriver.cpp
R2D = -I $(Include)/Renderer $(Include)/Renderer/R2D.cpp
Objects = $(Include)/Renderer/R3D.cpp $(Include)/Renderer/Poly.cpp  $(Include)/Renderer/Object.cpp 
Terminal = -I $(Include2) $(Include2)/terminal.cpp $(Include2)/TS2D.cpp
System =  -I $(Include)/System $(Include)/System/BBP3Process.cpp
Memory =  -I $(Include)/Memory $(Include)/Memory/Serializable.cpp

default:
	g++ -g $(Graphics) $(Math) $(Drivers) $(R2D) $(Objects) Out/ibp.cpp -o Out/ibpRefactor.exe
	g++ -g $(Graphics) $(Math) $(Drivers) $(R2D) $(Objects) $(Terminal) $(Window) Out/sysTerminal.cpp -o Out/sysRefactor.exe
	clear
sys:
	g++ -g $(Graphics) $(Math) $(Drivers) $(R2D) $(Objects) $(Terminal) $(System) $(Memory) Out/sysTerminal.cpp -o Out/sysRefactor.exe
	