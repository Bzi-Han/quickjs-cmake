#include <quickjs.h>

#include <iostream>

int main()
{
    auto runtime = JS_NewRuntime();
    auto context = JS_NewContext(runtime);
    auto jsResult = JS_Eval(context, "1 + 2", JS_EVAL_TYPE_GLOBAL, "<input>", 0);

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