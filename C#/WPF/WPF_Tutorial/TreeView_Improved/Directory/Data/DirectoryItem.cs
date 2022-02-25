using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TreeView_Improved
{
    // 드라이브, 파일, 폴더와 같은 디렉토리 아이템에 대한 정보 클래스, MVVM에서 모델(M)
    public class DirectoryItem
    {
        public DirectoryItemType Type { get; set; }
        public string? FullPath { get; set; }
        public string? Name { get { return Type == DirectoryItemType.Drive ? FullPath : DirectoryStructure.GetFileFolderName(FullPath); } }
    }
}
