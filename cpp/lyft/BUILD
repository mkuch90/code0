
cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [":autocomplete",
	    ":util",
	    "//external:gflags",
	    ],
)

cc_library(
    name = "lib",
    srcs = ["lib.cc"],
    hdrs = ["lib.h"],
)

cc_library(
    name = "autocomplete",

    srcs = ["autocomplete.cc"],
    hdrs = ["autocomplete.h"],
)

cc_test(
    name = "lib_test",
    srcs = ["lib_test.cc"],
    deps = [
        "@googletest//:gtest_main", 
        ":lib"
    ],
)   

cc_library(
    name = "util",
    srcs = ["util.cc"],
    hdrs = ["util.h"],
)

cc_test(
    name = "util_test",
    srcs = ["util_test.cc"],
    data = glob(
        ["testdata/*.txt"],
    ),
    deps = [
        "@googletest//:gtest_main", 
	":util"
    ],
)   

