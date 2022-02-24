using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TreeView_Improved
{
    public class DirectoryStructure
    {
        // C드라이브, D드라이브 등 찾기...
        public static List<DirectoryItem> GetLogicalDrives()
        {
            // Directory.GetLogicalDrives()는 컴퓨터에 달려있는 드라이브에 대한 정보가 들어간다.
            // 예를 들어 C드라이브, D드라이브 등...
            // Select는 람다식을 때려넣어서 데이터 변형을 시키는 경우에 사용한다.
            // 현재 코드에서는 string[]을 DirectoryItem[]로 치환하고 있다. 
            return Directory.GetLogicalDrives().Select(drive => new DirectoryItem { FullPath = drive, Type = DirectoryItemType.Drive }).ToList();
        }

        // 특정 폴더, 드라이브의 내부 요소 탐색
        public static List<DirectoryItem> GetDirectoryContents(string? fullPath)
        {
            var items = new List<DirectoryItem>();
            
            #region Get Folders

            try
            {
                var dirs = Directory.GetDirectories(fullPath);

                // 하위 아이템 추가
                if (dirs.Length > 0)
                    items.AddRange(dirs.Select(dir => new DirectoryItem { FullPath = dir, Type = DirectoryItemType.Folder }));
            }
            catch
            {

            }

            #endregion

            #region Get Files

            var fileList = new List<string>();
            try
            {
                var files = Directory.GetFiles(fullPath);

                // 하위 아이템 추가
                if (files.Length > 0)
                    items.AddRange(files.Select(file => new DirectoryItem { FullPath = file, Type = DirectoryItemType.File }));
            }
            catch
            {

            }

            #endregion

            return items;
        }

        #region Helpers
        public static string? GetFileFolderName(string? path)
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
