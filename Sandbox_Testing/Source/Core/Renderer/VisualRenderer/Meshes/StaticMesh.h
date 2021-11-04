//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file creates the ERSStaticMesh Struct/Functions.
    Additonal Notes: None
    Date Created: 2021-11-04
*/

struct ERSStaticMesh {

    // Create OpenGL Handles
    unsigned int VAO;
    unsigned int VBO;

    // Helper Bools
    bool _HasPopulated = false;


    // Creation Functions
    void SetupMesh(float Vertices[]) {

        // Setup Vertex Buffers
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        // Bind To Buffer
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // Push In Data
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

    }

    void BindVertexArray() {
        glBindVertexArray(VAO);
    } 




};