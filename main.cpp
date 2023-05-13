#include <iostream>
#include "GlobalVariable.h"
#include "type.h"
#include <string>
using namespace std;
//VarDef Visitor 函数(部分)伪代码示例（全局变量声明和初始化）
Type type = i32_Type;
string var_name = "";
int data = 0;
visitInitVarDef(InitVarDefContext *ctx){
    //访问子结点
    visitChildren(ctx);
    //s 为符号表，其中s.variable()可以调用该结构存储变量
    map<string, Value*> VariableCollection = s.variable();
    //end()函数表示遍历完变量的集合，没有找到相同命名的变量
    if(VariableCollection.find(var_name) != VariableCollection.end()) cout << " 重复命名" << endl;
    //判断该变量是否为全局变量
    if(ctx.isGlobal){
        //调用中端的GlobalVarible 函数，生成该全局变量声明和初始化过程的中间代码
        //参数说明：var_name(变量名),m(模块，一个源代码文件的抽象表达，参考附录 2.2 中的Module 类),i32_Type(数据类型),false(判定是否是常量变量,是否有const 关键字), ConstantInt::get(data, m)(将初始化的数据存储)
        GlobalVariable*gv=GlobalVariable::create(var_name,m,i32_Type,false, ConstantInt::get(data, m));
        //将变量名和中间代码到符号表s 中
        s.put(var_name, gv);	
    }
    return nullptr;
}
//visit 子结点代码示例
visitChildren(ParseTree *ctx) {

    for(int i=0;i< (int)ctx->children.size(); i++){
    //children.size()得到ctx 节点的子节点数
    //访问 bType 子结点获取变量类型
        if(ctx->children[i]->type == "bType"){
            visitBType(ctx->children[i]);
        }
        //访问 ident 子结点获取变量名
        else if(ctx->children[i]‐>type == "Ident"){

            visitIdent(ctx->children[i]);
            //访问 initVal 子结点获取变量的值，该过程(根据文法)涉及层层调用，为了方便理解直接写为访问存放数据的Number 结点
        }else if(ctx->children[i]->type == "initVal"){
            visitNumber(ctx->children[i]);
        }
    }
    return nullptr;  
}
visitBType(ParseTree *ctx) {

    type = ctx->getText();  
}
visitIdent(ParseTree *ctx) {
    var_name = ctx->getText();  
}
visitNumber(NumberContext *ctx) {
    data = ctx->getText();
}
int main(){
    GlobalVariable*gv=GlobalVariable::create(var_name,m,i32_Type,false, ConstantInt::get(data, m));
    return 0;
}