workspace "Bank"
    architecture "x86_64"
    platforms { "Win32", "x64" }
    configurations { "Debug", "Release" }
    location "BankApp"
    defaultplatform "x64"
    
    filter "platforms:Win32"
        architecture "x86"
    filter "platforms:x64"
        architecture "x86_64"
    filter {}

project "BankLib"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    targetdir "BankApp/BankLib/x64/$(Configuration)/"
    objdir "BankApp/BankLib/x64/$(Configuration)/obj/"    
    namespace "BankLib"
    
    files {
        "BankApp/BankLib/include/Account.h",
        "BankApp/BankLib/include/Currency.h",
        "BankApp/BankLib/include/Customer.h",
        "BankApp/BankLib/include/Socket.h",    
        "BankApp/BankLib/include/Controllers/AccountController.h",
        "BankApp/BankLib/include/Controllers/CustomerController.h",
        "BankApp/BankLib/include/Models/AccountModel.h",
        "BankApp/BankLib/include/Models/CustomerModel.h",
        "BankApp/BankLib/include/Repositories/AccountRepo.h",
        "BankApp/BankLib/include/Repositories/CustomerRepo.h",
        "BankApp/BankLib/include/Services/AccountService.h",
        "BankApp/BankLib/include/Services/CustomerService.h",
        "BankApp/BankLib/src/Currency.cpp",
        "BankApp/BankLib/src/Socket.cpp",
        "BankApp/BankLib/src/Controllers/AccountController.cpp",
        "BankApp/BankLib/src/Controllers/CustomerController.cpp",
        "BankApp/BankLib/src/Repositories/AccountRepo.cpp",
        "BankApp/BankLib/src/Repositories/CustomerRepo.cpp",
        "BankApp/BankLib/src/Services/AccountService.cpp",
        "BankApp/BankLib/src/Services/CustomerService.cpp",
    }
    
    includedirs {
        "BankApp/BankLib/include",
        "BankApp/BankLib/include/Controllers",
        "BankApp/BankLib/include/Models",
        "BankApp/BankLib/include/Repositories",
        "BankApp/BankLib/include/Services",
        "BankApp/BankLib/include/nlohmann",
    }
    
    defines {
        "WIN32",
        "_LIB",
        "UNICODE",
        "_UNICODE",
    }
    
    characterset "Unicode"
    
    filter "configurations:Debug"
        defines { "_DEBUG" }
        optimize "Off"
        runtime "Debug"
        symbols "On"
        floatingpoint "Fast"
    
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        runtime "Release"
        symbols "Off"
        floatingpoint "Fast"
    
    filter {}

project "BankApp"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "BankApp/BankRun/x64/$(Configuration)/"
    objdir "BankApp/BankRun/x64/$(Configuration)/obj/"
    
    files {
        "BankApp/BankRun/BankApp.cpp",
    }
    
    includedirs {
        "BankApp/BankLib/include",
        "BankApp/BankLib/include/Controllers",
        "BankApp/BankLib/include/Models",
        "BankApp/BankLib/include/Repositories",
        "BankApp/BankLib/include/Services",
    }
    
    links { "BankLib" }
    libdirs { "BankApp/BankLib/x64/$(Configuration)/" }
    
    defines {
        "WIN32",
        "_CONSOLE",
        "UNICODE",
        "_UNICODE",
    }
    
    characterset "MultiByte"
    
    filter "configurations:Debug"
        defines { "_DEBUG" }
        optimize "Off"
        runtime "Debug"
        symbols "On"
        floatingpoint "Fast"
    
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        runtime "Release"
        symbols "Off"
        floatingpoint "Fast"
    
    filter {}

project "Testing"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    
    targetdir "Testing/x64/$(Configuration)/"
    objdir "Testing/x64/$(Configuration)/obj/"
    
    files {
        "Testing/test.cpp",
    }
    
    includedirs {
        "BankApp/BankLib/include",
        "BankApp/BankLib/include/Controllers",
        "BankApp/BankLib/include/Models",
        "BankApp/BankLib/include/Repositories",
        "BankApp/BankLib/include/Services",
        "Testing/packages/Microsoft.googletest.v140.windesktop.msvcstl.static.rt-static.1.8.1.7/include",
    }
    
    libdirs {
        "BankApp/BankLib/x64/$(Configuration)/",
        "Testing/packages/Microsoft.googletest.v140.windesktop.msvcstl.static.rt-static.1.8.1.7/lib/native/v140/windesktop/msvcstl/static/rt-static/$(Configuration)/x64",
    }
    
    links {
        "BankLib",
        "gtest",
    }
    
    defines {
        "WIN32",
        "_CONSOLE",
        "UNICODE",
        "_UNICODE",
        "_VARIADIC_MAX=10",
    }
    
    characterset "Unicode"
    
    filter "configurations:Debug"
        defines { "_DEBUG" }
        optimize "Off"
        runtime "Debug"
        symbols "On"
        floatingpoint "Fast"
        buildoptions { "/Zi" }
    
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        runtime "Release"
        symbols "Off"
        floatingpoint "Fast"
    
    filter {}

filter {}
    project "BankApp"
        dependson { "BankLib" }
    
    project "Testing"
        dependson { "BankLib" }

filter {}    
    if _ACTION == "vs2022" then
        startproject "BankApp"
    end
