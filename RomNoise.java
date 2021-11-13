import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.SecureRandom;
import java.util.List;
import java.util.Scanner;
import java.util.TreeMap;
import java.util.stream.Collectors;

public final class RomNoise
{
  private RomNoise()
  {

  }

  private record CharacterData(int x, int y)
  {
  }

  public static void main(
    final String[] args)
    throws Exception
  {
    final var random = SecureRandom.getInstanceStrong();

    System.out.println("const uint8_t rom_random[256] PROGMEM = {");

    final var data = new byte[256];
    random.nextBytes(data);
    for (int index = 0; index < 256; ++index) {
      System.out.printf("0x%02x,", (int) data[index] & 0xff);
      if (index > 0 && index % 8 == 0) {
        System.out.println();
      }
    }

    System.out.println("};");
  }
}
