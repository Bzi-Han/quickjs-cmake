#include <quickjs.h>

#include <iostream>
#include <string>

int main()
{
    auto runtime = JS_NewRuntime();
    auto context = JS_NewContext(runtime);

    std::string script = "1 + 2 + 3";
    auto jsResult = JS_Eval(context, script.data(), script.size(), "<input>", JS_EVAL_TYPE_GLOBAL);

    int result = 0;
    if (0 == JS_ToInt32(context, &result, jsResult))
        std::cout << result << std::endl;
    else
        std::cout << "Error" << std::endl;

    JS_FreeValue(context, jsResult);
    JS_FreeContext(context);
    JS_FreeRuntime(runtime);

    return 0;
}