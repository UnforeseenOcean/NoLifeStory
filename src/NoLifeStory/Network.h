////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	namespace Network {
		void Init();
		void Loop();
		void Unload();
		extern bool Online;
		extern uint16_t Version;
		extern string Patch;
		extern uint8_t SendIV[4];
		extern uint8_t RecvIV[4];
		extern uint8_t Locale;
		extern string IP;
		extern uint16_t Port;
	}
	class Packet {
	public:
		vector<char> data;
		size_t pos;
		Packet() : pos(0), data() {}
		Packet(uint16_t opcode) : pos(0), data() { 
			Write<int32_t>(0);
			Write<uint16_t>(opcode);
		}
		void Send();
		template <class T>
		T Read() {
			T& ret = *(T*)&data[pos];
			pos += sizeof(T);
			return ret;
		}
		template <class T>
		void Write(T v) {
			data.insert(data.end(), (char*)&v, (char*)&v+sizeof(T));
		}
	};
	template <>
	inline string Packet::Read<string>() {
		size_t size = Read<uint16_t>();
		string s(&data[pos], size);
		pos += size;
		return s;
	}
	template <>
	inline void Packet::Write<string>(string s) {
		Write<uint16_t>(s.size());
		data.insert(data.end(), s.begin(), s.end());
	}
}
