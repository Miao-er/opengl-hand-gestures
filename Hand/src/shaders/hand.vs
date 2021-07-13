#version 450
		const int MAX_BONES = 100;
		uniform mat4 u_bone_transf[MAX_BONES];
		uniform mat4 u_mvp;
		layout(location = 0) in vec3 in_position;
		layout(location = 1) in vec2 in_texcoord;
		layout(location = 2) in vec3 in_normal;
		layout(location = 3) in ivec4 in_bone_index;
		layout(location = 4) in vec4 in_bone_weight;
		out vec2 pass_texcoord;
		out vec3 normal;
		out vec3 fragPos;
		void main() {
		    float adjust_factor = 0.0;
		    for (int i = 0; i < 4; i++) adjust_factor += in_bone_weight[i] * 0.25;
		    mat4 bone_transform = mat4(1.0);
		    if (adjust_factor > 1e-3) {
		        bone_transform -= bone_transform;
		        for (int i = 0; i < 4; i++)
		            bone_transform += u_bone_transf[in_bone_index[i]] * in_bone_weight[i] / adjust_factor;
			 }
		    gl_Position = u_mvp * bone_transform * vec4(in_position, 1.0);
		    pass_texcoord = in_texcoord;
			normal = in_normal;
			fragPos = vec3(bone_transform * vec4(in_position, 1.0));
			//fragPos = in_position;
		}
