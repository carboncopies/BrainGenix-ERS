##################
# BG BUILD UTIL #
##################

function(disable_target_warnings target)
    BGBuildLogger(${Green} "Disabling Warnings For Target ${target}")
    target_compile_options(${target} PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
            -w>
        $<$<CXX_COMPILER_ID:MSVC>:
        /w>
        )
    BGBuildLogger(${BoldGreen} "Disabled Warnings For Target ${target}")
endfunction()