// node test.js
const Minia = require("./minia.js");

async function testBasic() {
  console.log("🧪 Start test...");

  try {
    // load WebAssembly module
    const Module = await Minia();
    console.log("✅ WebAssembly Module load success");

    // test JSMinia
    const parser = new Module.JSMinia(["a = 1", "b = a + c", "d = hash(concat(\"test-\", e))"]);
    console.log("✅ JSMinia instance create success");

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
    console.log(result);
    // { a: 1n, b: 6n, d: 'test-minia' }

    // release memory
    parser.delete();

    console.log("✅ Pass All The tests！");
  } catch (error) {
    console.error("❌ Test Fail:", error);
    process.exit(1);
  }
}

// test all
async function runAllTests() {
  console.log("🎯 Minia local test");
  console.log("========================");

  await testBasic();
}

// run this file
if (require.main === module) {
  runAllTests().catch(console.error);
}

module.exports = { testBasic };
