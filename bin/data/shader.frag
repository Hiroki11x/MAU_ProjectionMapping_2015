uniform vec2 u_resolution; // 画面の解像度(width,height)
uniform float u_time; // 起動してからの経過時間(秒)
const int NUM = 20; // oFから受けとる波の配列
uniform float freq[20];  // 波の数だけくりかえす
/*void main() {
    float red = abs(sin(u_time * 30.0));
    float green = abs(sin(u_time * 40.0));
    float blue = abs(sin(u_time * 50.0));
    gl_FragColor = vec4(red, green, blue, 1.0);
}*///点滅

/*void main() {
    // 画面の解像度から、0.0~1.0に正規化する
    vec2 st = gl_FragCoord.xy/u_resolution;
    gl_FragColor = vec4(st.x,st.y,0.0,1.0);
}*///グラデーション

/*void main() {
    //画面の解像度から、0.0~1.0に正規化する
    vec2 st = gl_FragCoord.xy / u_resolution;
    // 色を格納する変数
    vec3 color;
    // RGBそれぞれの時間で変化するグラデーションを生成
    color.r = abs(sin(u_time * 1.5 + st.x));
    color.g = abs(sin(u_time * 2.0 + st.y));
    color.b = abs(sin(u_time * 3.0 + st.y));
    // 合成して出力
    gl_FragColor = vec4(color.r, color.g, color.b, 1.0);
}*///時間経過のグラデ

/*void main() {
    //画面の解像度から、0.0~1.0に正規化する
    vec2 st = gl_FragCoord.xy / u_resolution;
    // 画面の中央をy軸の中心に
    st.y -= 0.5;
    // Sin波で濃淡をつける
    st.y += sin(st.x * 10.0 + u_time) * 0.2 * sin(u_time);;
    // 1から引いて、乗算する
    vec3 color = vec3(1.0 - pow(abs(st.y), 0.2));
    // 色を設定
    gl_FragColor = vec4(color.r * 0.2, color.g * 0.5, color.b * 1.0, 1.0);
}*///sin波
void main() {
    vec3 color;
 
    for (int i = 0; i < NUM; i++) {
        //画面の解像度から、0.0~1.0に正規化する
        vec2 st = gl_FragCoord.xy / u_resolution;
        // 画面の中央をy軸の中心に
        st.y -= 0.5;
        // Sin波で濃淡をつける + 時間による変化
        st.y += sin(st.x * freq[i] + u_time) * 0.2 * sin(u_time * freq[i] * 0.1);
        // 1から引いて、乗算する
        color += vec3(1.0 - pow(abs(st.y), 0.75/float(NUM)));
        // 色を設定
        gl_FragColor = vec4(color.r * 0.2, color.g * 0.5, color.b * 1.0, 1.0);
    }
}

