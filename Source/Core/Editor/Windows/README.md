# Instructions To Add New Windows
Adding windows to ERS is a fairly simple process, and can be accomplished as follows:

    - Firstly, create a subdirectory here with the format "GUI_Window_{NameOfYourWindow}"
    - Next, Add the cmake and other info, just copy the structure of any existing one
    - Then, add that subdirectory you created to the CMakeLists.txt file in this directory "add_subdirectory({YourSubDir})"
    - Now, head over to the WindowManager Class located (../Utils/ERS_Editor_WindowManager)
    - 