#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// ウィンドウ関連の処理
class Window{
    GLFWwindow *const window;
    GLfloat aspect; //縦横比
    
public:
    //コンストラクタ
    Window(int width = 640, int height = 480, const char *title = "Hello!!") : window(glfwCreateWindow(width, height, title, NULL, NULL)){
        if(window == NULL){
            std::cerr << "Can't create GLFW window." << std::endl;
            exit(1);
        }
        //現在のウィンドウを処理対象にする
        glfwMakeContextCurrent(window);
        //GLEWを初期化
        glewExperimental = GL_TRUE;
        if(glewInit() != GLEW_OK){
            std::cerr << "Can't initialize GLEW." << std::endl;
            exit(1);
        }
        //垂直同期のタイミングを待つ
        glfwSwapInterval(1);
        //このインスタンスのthisポインタを記録しておく
        glfwSetWindowUserPointer(window, this);
        //ウィンドウのサイズ変更時に呼び出す処理を登録
        glfwSetWindowSizeCallback(window, resize);
        //開いたウィンドウの初期化
        resize(window, width, height);
    }
    
    // デストラクタ
    virtual ~Window(){
        glfwDestroyWindow(window);
    }
    // 描画ループの継続判定
    explicit operator bool(){
        // イベントを取り出す
        glfwWaitEvents();
        // ウィンドウを閉じる必要がなければ true を返す
        return !glfwWindowShouldClose(window);
    }
    // ダブルバッファリング
    void swapBuffers() const{
        // カラーバッファを入れ替える
        glfwSwapBuffers(window);
    }
    
    //ウィンドウのサイズ変更時の処理
    static void resize(GLFWwindow *const window, int width, int height){
        //フレームバッファのサイズを調べる
        int fbWidth, fbHeight;
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
        //フレームバッファ全体をビューポートに設定する
        glViewport(0, 0, fbWidth, fbHeight);
        //このインスタンスのthisポインタを得る
        Window *const instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));
        if(instance != NULL){
            //このインスタンスが保持する縦横比を更新する
            instance->aspect = static_cast<GLfloat>(width)/static_cast<GLfloat>(height);
        }
    }
    
    //縦横比を取り出す
    GLfloat getAspect() const{
        return aspect;
    }
};
