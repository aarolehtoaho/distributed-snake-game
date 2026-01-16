import pygame

class Renderer:
    SQUARE_SIZE = 20
    FONT_SIZE = 16
    FONT_COLOR = (255, 255, 255)
    BG_COLOR = (13, 17, 23)
    GRID_COLOR = (22, 27, 34)
    SQUARE_COLOR = (38, 166, 65)

    def __init__(self, width: int, height: int):
        pygame.init()
        self.text_panel_height = self.SQUARE_SIZE * 2
        self.screen = pygame.display.set_mode((width * self.SQUARE_SIZE,
                                               height * self.SQUARE_SIZE + self.text_panel_height))
        self.clock = pygame.time.Clock()
        self.font = pygame.font.SysFont('Consolas', self.FONT_SIZE)
        self.rows = height
        self.cols = width

    def clear_screen(self):
        self.screen.fill(self.BG_COLOR)

    def draw_square_border(self, row: int, col: int):
        square = pygame.Rect(col * self.SQUARE_SIZE,
                             row * self.SQUARE_SIZE + self.text_panel_height,
                             self.SQUARE_SIZE,
                             self.SQUARE_SIZE)
        pygame.draw.rect(self.screen, self.GRID_COLOR, square, 1)

    def draw_square(self, row: int, col: int, colored: bool = True):
        color = self.SQUARE_COLOR if colored else self.BG_COLOR
        square = pygame.Rect(col * self.SQUARE_SIZE,
                             row * self.SQUARE_SIZE + self.text_panel_height,
                             self.SQUARE_SIZE,
                             self.SQUARE_SIZE)
        pygame.draw.rect(self.screen, color, square)
        self.draw_square_border(row, col)

    def draw_grid(self, rows: int, cols: int):
        for row in range(rows):
            for col in range(cols):
                self.draw_square_border(row, col)

    def draw_text_panel(self, text: str):
        panel_rect = pygame.Rect(0,
                                 0,
                                 self.cols * self.SQUARE_SIZE,
                                 self.text_panel_height)
        pygame.draw.rect(self.screen,
                         self.BG_COLOR,
                         panel_rect)
        text_surface = self.font.render(text, True, self.FONT_COLOR)
        self.screen.blit(text_surface, (10, 10))

    def update_display(self):
        pygame.display.flip()
