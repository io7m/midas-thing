import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;
import java.util.Scanner;
import java.util.TreeMap;
import java.util.stream.Collectors;

public final class RomCode
{
  private RomCode()
  {

  }

  private record CharacterData(int x, int y)
  {
  }

  public static void main(
    final String[] args)
    throws Exception
  {
    if (args.length != 1) {
      System.err.println("usage: rom-map.txt");
      System.exit(1);
    }

    final List<String> lines;
    try (var stream = Files.lines(Paths.get(args[0]))) {
      lines =
        stream
          .filter(line -> !line.isBlank())
          .collect(Collectors.toList());
    }

    final var characters =
      new TreeMap<Character, CharacterData>();

    for (final var line : lines) {
      final var character =
        line.charAt(0);
      final var rest =
        line.substring(1).trim();

      try (var scanner = new Scanner(rest)) {
        final var x = scanner.nextInt();
        final var y = scanner.nextInt();
        characters.put(Character.valueOf(character), new CharacterData(x, y));
      }
    }

    System.out.println("const struct rom_character_t characters[128] = {");

    for (char ch = 0; ch < 128; ++ch) {
      final var data = characters.get(Character.valueOf(ch));
      if (data != null) {
        System.out.printf(
          """
              // Character (0x%x)
              { .source_x = %d, .source_y = %d },                   
            """,
          (int) ch,
          Integer.valueOf(data.x()),
          Integer.valueOf(data.y()));
      } else {
        System.out.printf(
          """
              // Character (0x%x)
              { .source_x = 120, .source_y = 120 },                   
            """,
          (int) ch);
      }
    }

    System.out.println("};");
  }
}
