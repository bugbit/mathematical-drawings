.PHONY: clean All

All:
	@echo "----------Building project:[ ManderbrotZoom - Debug ]----------"
	@cd "Draws/ManderbrotZoom/Allegro" && "$(MAKE)" -f  "ManderbrotZoom.mk"
clean:
	@echo "----------Cleaning project:[ ManderbrotZoom - Debug ]----------"
	@cd "Draws/ManderbrotZoom/Allegro" && "$(MAKE)" -f  "ManderbrotZoom.mk" clean
