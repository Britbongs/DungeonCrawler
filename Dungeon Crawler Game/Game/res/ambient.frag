#version 110
uniform sampler2D texture;

uniform vec4 ambientColor;
varying vec4 vColor;

void main()
{
	//(0.3f, 0.3f, 0.7f);
	//ambientColor = vec4
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec3 ambient = ambientColor.rgb * ambientColor.a; 
    vec4 a = vColor * pixel; 

    vec3 final = vec3( a.rgb * ambient);

    // multiply it by the color
    gl_FragColor = vec4(final, pixel.a);//gl_Color * pixel;
}