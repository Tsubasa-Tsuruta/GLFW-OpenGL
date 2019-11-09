#pragma once
#include <GL/glew.h>

//図形データ
class Object{
    GLuint vao; //頂点配列オブジェクト
    GLuint vbo; //頂点バッファオブジェクト
public:
    //頂点属性
    struct Vertex{
        GLfloat position[2];
    };
    //コンストラクタ
    Object(GLint size, GLsizei vertexcount, const Vertex *vertex){
        //頂点配列オブジェクト
        glGenVertexArrays(1, &vao); //1つの頂点配列オブジェクトを作成し、配列vaoに格納する
        glBindVertexArray(vao);
        
        //頂点バッファオブジェクト
        glGenBuffers(1, &vbo); //1つの頂点バッファオブジェクトを作成し、配列vboに格納する
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertexcount*sizeof(Vertex), vertex, GL_STATIC_DRAW);
        
        //結合されている頂点バッファオブジェクトをin変数から参照できるようにする
        glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, 0, 0); //図形の描画時にattrib変数が受け取るデータの格納場所と書式を設定
        glEnableVertexAttribArray(0);
    }
    
    //デストラクタ
    virtual ~Object(){
        //頂点配列オブジェクトを削除
        glDeleteVertexArrays(1, &vao);
        //頂点バッファオブジェクトを削除
        glDeleteBuffers(1, &vbo);
    }
    
private:
    // コピーコンストラクタによるコピー禁止
    Object(const Object &o);
    // 代入によるコピー禁止
    Object &operator=(const Object &o);
    
public:
    // 頂点配列オブジェクトの結合
    void bind() const{
        // 描画する頂点配列オブジェクトを指定する
        glBindVertexArray(vao);
    }
};
