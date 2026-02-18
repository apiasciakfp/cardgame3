package com.cardmultigame;

import org.junit.jupiter.api.Test;
import static org.assertj.core.api.Assertions.assertThat;

class SmokeTest {

    @Test
    void javaVersionIs21() {
        String version = System.getProperty("java.version");
        assertThat(version).startsWith("21");
    }

    @Test
    void scaffoldIsWired() {
        String name = "CardMultigame";
        assertThat(name).isNotEmpty();
    }
}
