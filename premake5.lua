workspace "Networking"
    architecture "x86_64"
    startproject "Server"
    configurations { "Debug", "Release" }

application = "Examples"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Renderer"

include "Networking"

include (application)