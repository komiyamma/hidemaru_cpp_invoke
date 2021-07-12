/* 
 * Copyright (c) 2017 Akitsugu Komiyama
 * under the Apache License Version 2.0
 */

#pragma once

#include <string>

namespace Hidemaru {
	namespace Text {
		class Encoding {
		public:
			// utf8��utf16��
			static std::wstring utf8_to_utf16(const std::string& text);

			// utf16��utf8��
			static std::string utf16_to_utf8(const std::wstring& text);

			// cp932��utf16��
			static std::wstring cp932_to_utf16(const std::string& text);

			// utf16��cp932��
			static std::string utf16_to_cp932(const std::wstring& text);
		};
	}
}