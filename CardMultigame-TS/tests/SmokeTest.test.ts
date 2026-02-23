import { describe, it, expect } from "vitest";

describe("SmokeTest", () => {
  it("toolchain works — true is true", () => {
    expect(true).toBe(true);
  });

  it("TypeScript types work — string concatenation", () => {
    const greeting: string = "Hello" + " " + "CardMultigame-TS";
    expect(greeting).toBe("Hello CardMultigame-TS");
  });
});
