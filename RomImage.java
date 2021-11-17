import javax.imageio.ImageIO;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;
import java.util.Scanner;
import java.util.TreeMap;
import java.util.stream.Collectors;

public final class RomImage
{
  private RomImage()
  {

  }

  public static void main(
    final String[] args)
    throws Exception
  {
    if (args.length != 1) {
      System.err.println("usage: rom.png");
      System.exit(1);
    }

    final var image = ImageIO.read(new File(args[0]));
    if (image.getWidth() % 8 != 0 || image.getHeight() % 8 != 0) {
      System.err.println("Image width and height must be divisible by 8");
      System.exit(1);
    }

    /*
     * Divide image into strips of 8 vertical 1-bit pixels.
     */

    final var output = new ByteArrayOutputStream();
    for (int y = 0; y < image.getHeight(); y += 8) {
      for (int x = 0; x < image.getWidth(); ++x) {
        var page = 0;

        for (int p = 0; p < 8; ++p) {
          final var rgb = image.getRGB(x, y + p) & 0b00000000_11111111_11111111_11111111;
          final var bit = rgb > 0 ? 1 : 0;
          page |= bit << p;
        }

        output.write(page & 0b11111111);
      }
    }

    final var bytes = new ByteArrayInputStream(output.toByteArray());
    for (;;) {
      for (int index = 0; index < 8; ++index) {
        final var data = bytes.read();
        if (data == -1) {
          return;
        }
        System.out.printf("0x%02x,", Integer.valueOf(data & 0xff));
      }
      System.out.println();
    }
  }
}
