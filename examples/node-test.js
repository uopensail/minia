// 加载编译好的模块
const Minia = require("../libminia.js");

async function testBasic() {
  console.log("🧪 开始基本功能测试...");

  try {
    // 加载WebAssembly模块
    const Module = await Minia();
    console.log("✅ WebAssembly模块加载成功");

    // 测试JSMinia
    const args = new Module.VectorString();
    args.push_back("a = 1");
    args.push_back("b = a + c");
    args.push_back("d = hash(concat(\"test-\", e))");
        
    const parser = new Module.JSMinia(args);
    console.log("✅ JSMinia实例创建成功");

    // 测试解析功能
    const input = {
      c: {
        type: 0,
        value: 5,
      },
      e: {
        type: 2,
        value: "minia",
      },
    };

    const result = parser.call(input);
    console.log(`📝 输入: "${input}"`);
    console.log(`📄 输出: "${result}"`);
    console.log("---", result);
    // { a: 1n, b: 6n, d: 'test-minia' }

    // 清理内存
    parser.delete();
    args.delete();

    console.log("✅ 所有测试通过！");
  } catch (error) {
    console.error("❌ 测试失败:", error);
    process.exit(1);
  }
}

// 运行所有测试
async function runAllTests() {
  console.log("🎯 Minia Parser 本地测试");
  console.log("========================");

  await testBasic();
}

// 如果直接运行此文件
if (require.main === module) {
  runAllTests().catch(console.error);
}

module.exports = { testBasic };
