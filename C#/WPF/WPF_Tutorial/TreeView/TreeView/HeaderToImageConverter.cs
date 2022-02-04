using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;
using System.Windows.Media.Imaging;

namespace TreeView
{
    // 전체 경로가 주어지면 특정 이미지 타입으로 변환하는 기능 수행
    [ValueConversion(typeof(string), typeof(BitmapImage))]
    public class HeaderToImageConverter : IValueConverter
    {
        public static HeaderToImageConverter Instance = new HeaderToImageConverter();
        public object? Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            // 전체 경로 획득
            var path = (string)value;

            if(path == null)
                return null;

            return new BitmapImage(new Uri($"pack://application:,,,/Images/drives.png"));
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
