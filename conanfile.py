from conans import ConanFile, CMake


class IpFilterConan(ConanFile):
    name = "hello"
    version = "0.1"
    license = "None"
    author = "Alex Shirkin shirkin39rus@gmail.com"
    url = "https://github.com/Panchos39/otus-cpp-second-assignment"
    description = "Otus C++ course ip filter task"
    topics = ("c++11", "c++14", "c++17")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    generators = "cmake"
    exports_sources = "src/*", "CMakeLists.txt", "include/*", "cmake/*"
    requires = (
        "gtest/1.11.0",
    )
    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

        # Explicit way:
        # self.run('cmake %s/hello %s'
        #          % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="include", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["hello"]
        if self.settings.compiler in ["gcc", "clang", "apple-clang"]:
            self.cpp_info.cxxflags = ["-std=c++17"]
