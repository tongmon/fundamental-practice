using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TreeView_Improved.Directory.Data
{
    // 드라이브, 파일, 폴더와 같은 디렉토리 아이템에 대한 정보 클래스
    public class DirectoryItem
    {
        public string FullPath { get; set; }
        public string? Name { get { return DirectoryStructure.GetFileFolderName(this.FullPath); } }
    }
}
