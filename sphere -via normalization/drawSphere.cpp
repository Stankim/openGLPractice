#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include "Sphere.cpp"
#include "./../shaders.cpp"
#include <stdio.h>
#include "audio_reader.cpp"
#include <vector>
using namespace std;
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

unsigned int sphere_smoothness = 4;

int sphere_type = 1;

bool record =true;

int framerate = 60;

bool controls = false;

glm::vec3 sphere_color = glm::vec3(0.2f, 0.5f, 0.3f);
glm::vec3 lightPos = glm::vec3(1.0f, 3.0f, 2.0f);
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

double clearColorRed = 0.3f;
double clearColorGreen = 0.3f;
double clearColorBlue = 0.3f;
double clearColorGamma = 1.0f;

float speed_of_rotation = 0.5;
glm::vec3 axis_of_rotation(0.0f, 1.0f, 0.0f);

float speed_of_revolution = 0.0;
glm::vec3 axis_of_revolution(0.0f, 0.0f, 1.0f);

glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float field_of_view = 45.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float yaw=-90.0f, pitch;
bool firstMouse = true;
float lastX = SCR_WIDTH / 2.0f , lastY= SCR_HEIGHT / 2.0f;



void framebuffer_size_callback(GLFWwindow *window, int width,int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void convertToMp4FileExtension(string* audio_file){
    int length = audio_file[0].length();
    audio_file[0][length-1] = '4';
    audio_file[0][length-2] = 'p';
    audio_file[0][length-3] = 'm';
}

void printUsage(){
    std::cout << "USAGE:"<< std::endl;
    std::cout << "spheretalk x.wav -option1 data -option2 data -option3 data"<<std::endl;
    std::cout << "Options:"<<std::endl;
    std::cout << "-smoothness {int} e.g. spheretalk -smoothness 4 \n\tNB: recommended values 0 - 4"<<std::endl;
    std::cout << "-model {1-8} e.g. spheretalk -model 2"<<std::endl;
    std::cout << "-clearColor {0.0,0.0,0.0,0.0} e.g. spheretalk -clearColor 0.7,1.0,0.4,1.0  \n\tNB:The numbers must be between 0 and 1."<<std::endl;
    std::cout << "-sphereColor {0.0,0.0,0.0,0.0} e.g spheretalk -sphereColor 0.3,0.6,0.5,1.0  \n\tNB:The numbers must be between 0 and 1."<<std::endl;
    std::cout << "-speedOfRotation {float} e.g. spheretalk -speedOfRotation 0.3"<<std::endl;
    std::cout << "-controls {true|false} e.g. spheretalk -controls true"<<std::endl;
    std::cout << "-record {true|false} e.g. spheretalk -record true"<<std::endl;
    std::cout << "-framerate {int} e.g. spheretalk -framerate 60 \n\tNB:Video frames per second: Recommended 60."<<std::endl;
}
 glm::vec4 splitVec4Input(char * arg){
    glm::vec4 input;
    int length = strlen(arg);
    string number;
    int j=0;
    for(int i=0;i<length;i++){
        if(j>=4){
            std::cout<< "Error: Invalid input. Only 4 values required here: "<< arg <<std::endl;
            //system.exit();
        }
        if(arg[i]==',' || i==length-1){
            input[j] = atof(number.c_str());
            j++;
        }
        number.push_back(arg[i]);
    }
    return input;
 }

int main(int argc, char**argv)
{

    if(argc==1){
            printf("Error: The input provided is not adequate. Provide a wav file atleast.\n");
            return 0;
    }
    if(argc >= 2){
            int length = strlen(argv[1]);
            if(!(argv[1][length-4] == '.' 
                && argv[1][length-3] == 'w'
                && argv[1][length-2] == 'a'
                && argv[1][length-1] == 'v'))
            {
                printf("The second argument is not a .wav file.\n");
                return 0;
             }
        }
    char* audio_file = argv[1];
    FILE* f = fopen(audio_file, "r");
    if(f==NULL){
        printf("File does not exist in this folder.\n");
        return 0;
    }
    fclose(f);


for(int i = 2; i<argc;i+=2){
    if(argv[i][0] != '-'){
        cout<< "Error: No match for " << argv[i] << ". Try the available options."<<std::endl;
        printUsage();
        return 0;
    }
    if(i==argc-1){
        cout << "Error: No data passed in for option " << argv[i] << std::endl;
        printUsage();
        return 0;
    }
    if(strcmp(argv[i], "-smoothness")==0){
        sphere_smoothness = atoi(argv[i+1]);
    }
    if(strcmp(argv[i], "-model")==0)
    {
        sphere_type = atoi(argv[i+1]);
        if(sphere_type<1 || sphere_type>8){
            std::cout<< "Error: The option -model can only accept a value between 1 and 8."<<std::endl;
            return 0;
        }
    }
    if(strcmp(argv[i], "-clearColor")==0){
        glm::vec4 input = splitVec4Input(argv[i+1]);
        clearColorRed = input.x;
        clearColorGreen = input.y;
        clearColorBlue = input.z;
        clearColorGamma = input.w;
    }
    if(strcmp(argv[i], "-sphereColor")==0){
        sphere_color = splitVec4Input(argv[i+1]);
    }
    if(strcmp(argv[i], "-speedOfRotation")==0){
        speed_of_rotation = atof(argv[i+1]);
    }
    if(strcmp(argv[i], "-controls")==0){
        if(strcmp(argv[i+1], "true")==0){
            controls = true;
        }
        else if(strcmp(argv[i+1], "false")==0){
            controls = false;
        }
    }
    if(strcmp(argv[i], "-record")==0){
        if(strcmp(argv[i+1], "true")==0){
            record = true;
        }
        else if(strcmp(argv[i+1], "false")==0){
            record = false;
        }
    }
    if(strcmp(argv[i], "-framerate")==0){
        framerate = atoi(argv[i+1]);
    }
}




glfwInit();
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

GLFWwindow* window= glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "My own copy, openGL example", NULL, NULL);
if(window==NULL)
{
std::cout<<"Failed to create GLFW window"<< std::endl;
glfwTerminate();
return -1;
}
glfwMakeContextCurrent(window);
glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

if(controls){
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
}


if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
{
std::cout << "Failed to initialize GLAD" << std::endl;
return -1;
}
glEnable(GL_DEPTH_TEST);



string mp4_file_name = audio_file;

convertToMp4FileExtension(&mp4_file_name);
// start ffmpeg telling it to expect raw rgba 720p-60hz frames
// -i - tells it to read frames from stdin
string cmd = "ffmpeg  -r " 
+ to_string(framerate) 
+ " -f rawvideo -pix_fmt rgba -s " 
+ to_string(SCR_WIDTH) + "x" + to_string(SCR_HEIGHT) 
+ " -i - -threads 0 -preset fast -y -pix_fmt yuv420p -crf 21 -vf vflip \""
+ "T_" + mp4_file_name + "\"";

// open pipe to ffmpeg's stdin in binary write mode
FILE* ffmpeg = record? popen(cmd.c_str(), "w"):NULL;
int* buffer = new int[SCR_WIDTH*SCR_HEIGHT];


Shader sphereShader = Shader("sphere.vs", "sphere.fs");

AudioReader audio_reader = AudioReader(audio_file);

int audio_to_video_sample_step = audio_reader.sampleRateForAllChannels/ 60;

unsigned int VBO, VAO;
for(int audio_index=0;!glfwWindowShouldClose(window) && audio_index<audio_reader.framecount;audio_index+=audio_to_video_sample_step){

float audio_state = (float)audio_reader.data[audio_index];
audio_state = 1 - (audio_state/32768);
Sphere sphere = Sphere(sphere_smoothness,sphere_color,audio_state);
switch(sphere_type){
    case 1:
        sphere = Sphere(sphere_smoothness,sphere_color,audio_state);
    break;
    case 2:
        sphere = Sphere(sphere_smoothness,sphere_color, 0 , audio_state);
        break;
    case 3:
        sphere = Sphere(sphere_smoothness,sphere_color, 1 ,audio_state);
        break;
    case 4:
        sphere = Sphere(sphere_smoothness,sphere_color, -1 ,audio_state);
        break;
    case 5:
        sphere = Sphere(sphere_smoothness,sphere_color, audio_state , 1);
        break;
    case 6:
        sphere = Sphere(sphere_smoothness,sphere_color, audio_state , 0);
        break;
    case 7:
        sphere = Sphere(sphere_smoothness,sphere_color, audio_state , -1);
        break;
    case 8:
        sphere = Sphere(sphere_smoothness,sphere_color, 0 , -1+2*audio_state);
        break;
}


glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sphere.vertices.size() * sizeof(Vertex), &sphere.vertices[0], GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
glEnableVertexAttribArray(0);


glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
glEnableVertexAttribArray(1);



glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);



//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


float currentFrame = static_cast<float>(glfwGetTime());
deltaTime = currentFrame - lastFrame;
lastFrame = currentFrame;


processInput(window);
glClearColor(clearColorRed, clearColorGreen, clearColorBlue, clearColorGamma);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glm::mat4 projection;
projection = glm::perspective(glm::radians(field_of_view), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 100.0f); 

glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition+cameraFront, cameraUp);
//view[0][0] = (float)SCR_HEIGHT/ (float)SCR_WIDTH;

//cout<<view[0][0]<<endl;

glm::mat4 model = glm::mat4(1.0f);
model = glm::rotate(model, speed_of_rotation *(float)glfwGetTime(), axis_of_rotation);
model = glm::rotate(model,speed_of_revolution*(float)glfwGetTime(), axis_of_revolution);
sphereShader.use();

sphereShader.setMat4("model", model);
sphereShader.setMat4("view", view);	
sphereShader.setMat4("projection", projection);

sphereShader.setVec3("lightPos", lightPos);
sphereShader.setVec3("lightColor", lightColor);
sphereShader.setVec3("sphereColor", sphere.color);

glBindVertexArray(VAO);
glDrawArrays(GL_TRIANGLES, 0, sphere.vertices.size());
glfwSwapBuffers(window);
glfwPollEvents();

if(record){
    glReadPixels(0, 0, SCR_WIDTH, SCR_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    fwrite(buffer, sizeof(int)*SCR_WIDTH*SCR_HEIGHT, 1, ffmpeg);
}
}

pclose(ffmpeg);

glDeleteVertexArrays(1, &VAO);
glDeleteBuffers(1, &VBO);
glDeleteProgram(sphereShader.ID);

glfwTerminate();

if(record){
    string combine_audio_with_video = "ffmpeg -i \"T_"
     + mp4_file_name + "\" -i "
    + "\"" + audio_file + "\""
    + " -c:v copy -c:a aac "
    + "\"" + mp4_file_name + "\"";

    system(combine_audio_with_video.c_str());
}
return 0;
}


void processInput(GLFWwindow *window){
if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
glfwSetWindowShouldClose(window, true);
const float cameraSpeed = 2.5f * deltaTime;
if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	cameraPosition += cameraSpeed * cameraFront;
if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	cameraPosition -= cameraSpeed * cameraFront;
if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height){
glViewport(0,0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    cameraFront = glm::normalize(direction);
    
} 

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
field_of_view -= (float) yoffset;
if(field_of_view<1.0f)
	field_of_view = 1.0f;
if(field_of_view > 45.0f)
	field_of_view = 45.0f;
}
