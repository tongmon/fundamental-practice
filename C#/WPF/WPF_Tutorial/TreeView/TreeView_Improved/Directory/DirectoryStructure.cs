using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TreeView_Improved.Directory
{
    public class DirectoryStructure
    {
        #region Helpers
        public static string? GetFileFolderName(string path)
        {
            // 주어진 경로가 없으면 null 반환
            if (string.IsNullOrEmpty(path))
                return null;

            // 경로 정규화
            var normalizePath = path.Replace('/', '\\');

            // 마지막 \ 녀석의 인덱스 찾기
            var lastIndex = normalizePath.LastIndexOf('\\');

            // \를 찾지 못했으면 주어진 경로 반환
            if (lastIndex <= 0)
                return path;

            // 파일 이름을 획득
            return path.Substring(lastIndex + 1);
        }
        #endregion
    }
}
