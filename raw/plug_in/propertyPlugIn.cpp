#include <iostream>
#include "clang/AST/ASTContext.h"
#include "clang/AST/DeclObjC.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/FrontendPluginRegistry.h"

using namespace clang;
using namespace std;
using namespace llvm;
using namespace clang::ast_matchers;





namespace PropertyPlugIn {
  


    class FilterCallback: public MatchFinder::MatchCallback{
    private:
        CompilerInstance &CI;
        
        bool isCustom(const string fileName){
            if (fileName.empty()) return false;
            // 非 Xcode 中的源码都认为是用户的
            if (fileName.find("/Applications/Xcode.app/") == 0) return false;
            return true;
        }
        
        //   判断是否应该用  copy  修饰
        bool copyApplys(const string typeStr){
            if (typeStr.find("NSString") != string::npos ||
                typeStr.find("NSArray") != string::npos ||
                typeStr.find("NSDictionary") != string::npos) {
                return true;
            }
            return false;
        }
        
        
    public:
        FilterCallback(CompilerInstance &CI):CI(CI){  }
        
        void run(const MatchFinder::MatchResult &Result) override {
            // Result 通过 tag 获取到节点
            const ObjCPropertyDecl * propertyDecl = Result.Nodes.getNodeAs<ObjCPropertyDecl>("propObjC");
            string fileName = CI.getSourceManager().getFilename(propertyDecl->getSourceRange().getBegin()).str();
            //  判断节点有值, 且为用户文件
            if (propertyDecl && isCustom(fileName)) {
                // 拿到节点的类型
                string propType = propertyDecl->getType().getAsString();
                
                //拿到节点的描述信息
                ObjCPropertyAttribute::Kind attrKind = propertyDecl->getPropertyAttributes();
                
                if (copyApplys(propType) && !(attrKind & ObjCPropertyAttribute::kind_copy)){
                    //  诊断器
                    DiagnosticsEngine &diag = CI.getDiagnostics();
                    //  报告，  Report
                    //  第一个参数，警告放在哪个位置
                    //  第 2 个参数，警告的标识
                    diag.Report(propertyDecl->getBeginLoc(),diag.getCustomDiagID(DiagnosticsEngine::Error, "%0  该属性 ，不 copy，  后果 ..."))<<propType;
                }
            }
        }
    };


    //自定义的 PropConsumer
    class PropConsumer: public ASTConsumer{
        
    private:
        //AST节点的查找过滤器!
        MatchFinder filter;
        FilterCallback callback;
        
    public:
        PropConsumer(CompilerInstance &CI):callback(CI){
            // 添加过滤器，并指定关注的节点类型
            // 回调在 FilterCallback 里面的 run 方法
            // bind, 是对节点，做一个标记
            // objcPropertyDecl, OC 属性声明，对应我们关心的属性
            // 解析的时候，绑定
            filter.addMatcher(objcPropertyDecl().bind("propObjC"), &callback);
        }
        /*
        //解析完一个顶级的声明就回调一次!
        bool HandleTopLevelDecl(DeclGroupRef D) override{
            cout<<"正在解析...."<<endl;
            return true;
        }
        */
        //整个文件都解析完成的回调!
        void HandleTranslationUnit(ASTContext &Ctx) override {
            // 简单理解就是，解析完成，就把语法树，给过滤器
            filter.matchAST(Ctx);
        }
        
    };



    //继承 PluginASTAction ，实现我们自定义的 Action
    class PropASTAction:public PluginASTAction{

        public:
        bool ParseArgs(const CompilerInstance &CI, const std::vector<std::string> &arg) override{
            return true;
        }
        
        
        
        // ASTConsumer, 是一个抽象语法树的接口
        
        unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI, StringRef InFile) override{
            return unique_ptr<PropConsumer>(new PropConsumer(CI));
        }
        
    };
 

}



//注册插件
static FrontendPluginRegistry::Add<PropertyPlugIn::PropASTAction> PropertyPlugInName("name of PropertyPlugIn","description of PropertyPlugIn");





