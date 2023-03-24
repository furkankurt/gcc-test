CXXFLAGS=-std=c++17 -I../lib

RED=\e[31m
GREEN=\e[32m
BLUE=\e[34m
YELLOW=\e[33m
BOLD=\e[1m
RESET=\e[0m
NC=\033[0m

all: aranet

aranet: src/main.cpp
	@echo "$(BLUE)==================================================$(NC)"
	@echo "$(BOLD)$(YELLOW)Compiling code...$(NC)"
	$(CXX) $(CXXFLAGS) -o $@ $^
	@if [ "$$?" -ne 0 ]; then \
		@echo "$(BOLD)$(RED)Compiling Error!$(NC)" \
	    exit 1; \
	fi
	@echo "$(BOLD)$(YELLOW)Compiling success!$(NC)"
	@echo "$(BLUE)==================================================$(NC)"
	
	@echo "$(GREEN)For parse encoded base64 values, use this commad:$(NC)"
	@echo "$(BOLD)$(GREEN)./aranet E0ABAkmCAwQ=$(NC)"
	@echo "$(BLUE)==================================================$(NC)"
	@echo "$(GREEN)For parse 8 byte hex numbers, use this commad:$(NC)"
	@echo "$(BOLD)$(GREEN)./aranet 0x8730000837000258$(NC)"
	@echo "$(BLUE)==================================================$(NC)"
	@echo "$(GREEN)For clear the compiled 'aranet' code, use this command:$(NC)"
	@echo "$(BOLD)$(GREEN)make clean$(NC)"
	@echo "$(BLUE)==================================================$(NC)"

clean:
	rm -f aranet
	@echo "$(BOLD)$(GREEN)Cleared.$(NC)"
