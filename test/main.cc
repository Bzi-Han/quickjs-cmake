#include <quickjs.h>
#include <quickjs-libc.h>

#include <iostream>
#include <string>

const char script[] = R"(
    import * as os from "os";

    console.log('[=] message from console.log');

    let timers = [];
    for(let i = 0; i < 4; i++)
        timers[i] = os.setTimeout(() => print('[=] test timer'), 1000);
    for(let i = 0; i < 3; i++)
        os.clearTimeout(timers[i]);

    new Promise((resolve, reject) => {
        print('[=] test promise');
        os.setTimeout(() => resolve(), 1000);
    }).then(() => {
        print('[+] test promise resolve');
    }).catch(() => {
        print('[-] test promise catch');
    }).finally(() => {
        print('[=] test promise finally');
    });

    const test_async = async () => {
        print('[=] test async');
        new Promise((resolve, reject) => {
            reject({code: 400});
        }).catch((error) => print('[=] test async promise reject', error, error.code));
        print('[+] test async end');
    };

    const main = async () => {
        print('[=] main');
        await test_async();
        print('[=] main end');
    };

    main();
)";

int main()
{
    auto runtime = JS_NewRuntime();
    if (nullptr == runtime)
    {
        std::cout << "Failed to create js runtime" << std::endl;
        return 1;
    }
    auto context = JS_NewContext(runtime);
    if (nullptr == context)
    {
        std::cout << "Failed to create js context" << std::endl;
        return 1;
    }

    js_std_init_handlers(runtime);           // init event handlers
    js_std_add_helpers(context, 0, nullptr); // add helpers like 'console', 'print'
    js_init_module_os(context, "os");        // register module 'os'

    auto result = JS_Eval(context, script, sizeof(script) - 1, "<input>", JS_EVAL_TYPE_MODULE);
    if (JS_IsException(result))
    {
        js_std_dump_error(context);
        return 1;
    }
    JS_FreeValue(context, result);

    js_std_loop(context);

    js_std_free_handlers(runtime);
    JS_FreeContext(context);
    JS_FreeRuntime(runtime);

    return 0;
}