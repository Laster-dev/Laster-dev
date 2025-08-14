# Hi, I'm Laster-dev! 👋

Welcome to my GitHub profile! I'm a passionate developer with a keen interest in exploring emerging technologies and contributing to impactful projects. Here's a brief overview of my background and interests.

## 🚀 About Me
- 🌱 Currently expanding my knowledge base by learning new programming languages and frameworks.
- 💼 Seeking opportunities to collaborate on open-source initiatives and contribute to the developer community.
- 📫 Contact: 2857211723@qq.com

## 🛠️ Languages and Tools
- **Languages:** Python, C#, C++

## 🔬 Featured Project: Minimal Windows Shellcode Loader

This repository contains a highly optimized, minimal Windows shellcode loader with the following characteristics:

### ✨ Key Features
- **Ultra-minimal size**: Only 2KB (2048 bytes) executable
- **Pure Windows API**: No C runtime library dependencies
- **HTTP/HTTPS download**: Fetches shellcode from any URL
- **Memory execution**: Allocates and executes in-memory payloads
- **Cross-platform build**: Supports both 32-bit and 64-bit architectures

### 🏗️ Technical Highlights
- Uses `WinMainCRTStartup()` custom entry point to avoid CRT
- Implements HTTP client using WinINet API
- Dynamic memory management with `VirtualAlloc()`
- Proper memory protection transitions (RW → RX)
- Aggressive compiler optimizations for size reduction

### 📊 Build Results
```
Binary Size: 2048 bytes (2KB)
Format: PE32/PE32+ Windows executable
Dependencies: kernel32.dll, wininet.dll only
CRT Dependency: None
```

### 🔧 Quick Build
```bash
# 64-bit version
make x64

# 32-bit version  
make mingw

# Size comparison
make size
```

For detailed technical documentation, see [TECHNICAL_DETAILS.md](TECHNICAL_DETAILS.md) and [SHELLCODE_LOADER_README.md](SHELLCODE_LOADER_README.md).

## 📈 GitHub Stats
![Laster-dev's GitHub stats](https://github-readme-stats.vercel.app/api?username=Laster-dev&show_icons=true&theme=radical)

![CH563's used](https://github-readme-stats.vercel.app/api/top-langs/?username=Laster-dev&layout=compact)

Feel free to browse my repositories. I'm always open to discussing potential collaborations or answering any questions you might have!
